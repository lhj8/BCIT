import sys
import os
import argparse
import pandas as pd
import pickle

from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler

from sklearn.metrics import classification_report
from scripts import preprocess as ref
from sklearn.model_selection import train_test_split
from models import GBC
from models import CCA
from models import SVM
from models import KNN
from models import SKB
from models import RFE


ORIGINAL_CSV = './data/UNSW-NB15-BALANCED-TRAIN.csv'

features = ['srcip', 'sport', 'dstip', 'dsport',
            'proto', 'state', 'dur', 'sbytes',
            'dbytes', 'sttl', 'dttl', 'sloss',
            'dloss', 'service',	'Sload', 'Dload',
            'Spkts', 'Dpkts', 'swin', 'dwin',
            'stcpb', 'dtcpb', 'smeansz', 'dmeansz',
            'trans_depth', 'res_bdy_len', 'Sjit', 'Djit',
            'Stime', 'Ltime', 'Sintpkt', 'Dintpkt',	'tcprtt',
            'synack', 'ackdat',	'is_sm_ips_ports', 'ct_state_ttl',
            'ct_flw_http_mthd',	'is_ftp_login',	'ct_ftp_cmd', 'ct_srv_src',
            'ct_srv_dst', 'ct_dst_ltm',	'ct_src_ ltm', 'ct_src_dport_ltm',
            'ct_dst_sport_ltm',	'ct_dst_src_ltm', 'attack_cat',	'Label']


def remove_existing_csv():
    directory = './data'

    # Filename to exclude from deletion
    exclude_file = 'UNSW-NB15-BALANCED-TRAIN.csv'

    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        if filename.endswith('.csv') and filename != exclude_file:
            os.remove(file_path)
            print(f"Removed: {filename}")


def get_args(args):
    parser = argparse.ArgumentParser(description="COMP8085 Project 1")
    task_group = parser.add_mutually_exclusive_group(required=True)

    parser.add_argument('test_set',
                        type=str,
                        help='Path to held-out test set, in CSV format')
    parser.add_argument('classification_method',
                        type=str,
                        help='Selected classification method name')
    task_group.add_argument('--Label',
                            dest='task',
                            action='store_const',
                            const='Label',
                            help='Predict whether the packet is normal or not')
    task_group.add_argument('--attack_cat',
                            dest='task',
                            action='store_const',
                            const='attack_cat',
                            help='Predict the attack category')
    
    parser.add_argument('--pickle_file',
                        type=str,
                        required=False,
                        help='File name for the pickle object containing model or data')
    return parser


function_hashmap = {
    'CCA': CCA.correlation_coefficient,
    'SVM': SVM.SVM,
    'GBC': GBC.gbc_model,
    'RFE': RFE.rfe_model,
    'KNN': KNN.knn_model,
    'SKB': SKB.skb,
}


def run_function_by_key(key, training_data, test_data, validate_data, target):
    if key in function_hashmap:
        function_to_run = function_hashmap[key]
        # TODO: Need to find out what will be the arguments
        #       for our classifier
        function_to_run(training_data, test_data, validate_data, target)
    else:
        print(f"No function found for key: {key}")


def main():
    remove_existing_csv()
    args = get_args(sys.argv[1:]).parse_args()

    # Read csv using pandas in Latin mode
    original_csv = pd.read_csv(ORIGINAL_CSV,
                               encoding='ISO-8859-1',
                               low_memory=False)

    # Process data - change values of ports and null + factorize
    df = ref.preprocess_data(original_csv)

    # Split original csv into train and validate+test (0.7 : 0.3)
    train_df, validate_test_df = train_test_split(df,
                                                  train_size=0.7,
                                                  shuffle=True,
                                                  stratify=df['attack_cat'],
                                                  random_state=32)

    # Split validate+test into validate and test (0.5 : 0.5)
    validate_df, test_df = train_test_split(validate_test_df,
                                            train_size=0.5,
                                            shuffle=True,
                                            stratify=validate_test_df[
                                                'attack_cat'],
                                            random_state=34)

    # Save in to csv format
    train_df.to_csv('./data/train_data.csv', index=False)
    test_df.to_csv('./data/test_data.csv', index=False)
    validate_df.to_csv('./data/validate_data.csv', index=False)

    # print(df.shape)
    # print(train_df.shape)
    # print(validate_df.shape)
    # print(test_df.shape)

    # Run
    if (args.pickle_file):
        with open(args.pickle_file, 'rb') as file:
            RFE_attack_cat_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl','service', 'Sload', 'stcpb', 'smeansz', 'dmeansz', 'Ltime', 'Sintpkt','synack', 'ct_srv_dst']
            RFE_Label_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl', 'Sload', 'Dload', 'dmeansz', 'res_bdy_len', 'Sjit', 'Djit', 'Stime', 'Ltime', 'Sintpkt']

            loaded_model = pickle.load(file)
            if (args.classification_method == "SVM"):
                if (args.task == "Label"):
                    #SVM only
                    scaler = StandardScaler()
                    label_train = train_df[RFE_Label_X]
                    label_test = train_df[RFE_Label_X]
                    y_test = train_df["Label"]

                    X_train_scaled = scaler.fit_transform(label_train)
                    X_test_scaled = scaler.transform(label_test)


                    
                    y_pred = loaded_model.predict(X_test_scaled)
                    print(classification_report(y_test, y_pred))
                if (args.task == "attack_cat"):
                    #SVM only
                    scaler = StandardScaler()
                    attack_cat_train = train_df[RFE_attack_cat_X]
                    attack_cat_test = train_df[RFE_attack_cat_X]
                    y_test = train_df["attack_cat"]
                    
                    X_train_scaled = scaler.fit_transform(attack_cat_train)
                    X_test_scaled = scaler.transform(attack_cat_test)


                    
                    y_pred = loaded_model.predict(X_test_scaled)
                    print(classification_report(y_test, y_pred, zero_division=0))
            elif args.classification_method == "GBC":
                if args.task == "Label":
                    label_test = train_df[RFE_Label_X]
                    y_test = train_df["Label"]
                    y_pred = loaded_model.predict(label_test)
                    print(classification_report(y_test, y_pred))
                if args.task == "attack_cat":
                    attack_cat_test = train_df[RFE_attack_cat_X]
                    y_test = train_df["attack_cat"]
                    y_pred = loaded_model.predict(attack_cat_test)
                    print(classification_report(y_test, y_pred, zero_division=0))

            elif (args.classification_method == "KNN"):
                if (args.task == "Label"):
                    # KNN only
                    print(f"Loading pickle {args.task}")
                    scaler = StandardScaler()
                    label_train = train_df[RFE_Label_X]
                    label_test = train_df[RFE_Label_X]
                    y_test = train_df["Label"]

                    X_train_scaled = scaler.fit_transform(label_train)
                    X_test_scaled = scaler.transform(label_test)

                    y_pred = loaded_model.predict(X_test_scaled)
                    print(classification_report(y_test, y_pred))
                elif args.task == "attack_cat":
                    #KNN only
                    print(f"Loading pickle {args.task}")
                    scaler = StandardScaler()
                    attack_cat_train = train_df[RFE_attack_cat_X]
                    attack_cat_test = train_df[RFE_attack_cat_X]
                    y_test = train_df["attack_cat"]

                    X_train_scaled = scaler.fit_transform(attack_cat_train)
                    X_test_scaled = scaler.transform(attack_cat_test)

                    y_pred = loaded_model.predict(X_test_scaled)
                    print(classification_report(y_test, y_pred, zero_division=0))
    else:
        run_function_by_key(args.classification_method,
                        train_df,
                        test_df,
                        validate_df,
                        args.task)

    return 0


if __name__ == "__main__":
    main()
