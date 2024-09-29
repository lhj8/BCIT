import time
import pickle
import numpy as np
import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import precision_recall_fscore_support, classification_report
from sklearn.preprocessing import StandardScaler
from models import RFE

def print_elapsed_time(start_time, end_time):
    elapsed_time = end_time - start_time
    print(f"Time elapsed: {elapsed_time:.2f} seconds")
def knn_model(training_data, test_data, validation_data, target):
    start_time = time.time()
    Y_train = training_data[target]
    X_train = training_data.drop(['srcip', 'dstip','Label', 'attack_cat'], axis=1)

    Y_test = test_data[target]
    X_test = test_data.drop(['srcip', 'dstip','Label', 'attack_cat'], axis=1)

    Y_validate = validation_data[target]
    X_validate = validation_data.drop(['srcip', 'dstip','Label', 'attack_cat'], axis=1)

    # 96% -> 99%
    # ~40% -> 46%
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)
    X_validate = scaler.transform(X_validate)

    record_val_accuracy = []
    # Find the best hyperparameter k based on validation set accuracy
    # best_k, best_score = 0, 0
    # for k in range(1, 5, 1):
    #     print('Attempt k:', k)
    #     neigh = KNeighborsClassifier(n_neighbors=k, weights='distance', metric='manhattan', n_jobs=5)
    #     neigh.fit(X_train, Y_train)
    #     y_val_pred = neigh.predict(X_validate)
    #     score = neigh.score(X_validate, Y_validate)
    #     mar_precision, mar_recall, mar_f1_score, _ = precision_recall_fscore_support(Y_validate, y_val_pred, average='macro')
    #     record_val_accuracy.append(mar_f1_score)
    #
    #     print('f1 score: ', mar_f1_score)
    #     if mar_f1_score > best_score:
    #         best_k, best_score = k, mar_f1_score
    #         print('New best: ', k, mar_f1_score)
    #         print('New best score:' , score)

    if target == "Label":
        # Retrain the model with the best hyperparameter on the combined training and validation set
        final_model = KNeighborsClassifier(n_neighbors=5, weights='distance', metric='manhattan', n_jobs=5)
        final_model.fit(np.concatenate([X_train, X_validate]), np.concatenate([Y_train, Y_validate]))

        Y_test_pred = final_model.predict(X_test)
        print("\n==========Label Scores for all features ==========")
        print(f"{classification_report(Y_test_pred,Y_test, labels=[0,1], zero_division=0)}")
        end_time = time.time()
        print_elapsed_time(start_time, end_time)

    elif target == "attack_cat":
        # Retrain the model with the best hyperparameter on the combined training and validation set
        final_model = KNeighborsClassifier(n_neighbors=5, weights='distance', metric='manhattan', n_jobs=5)
        final_model.fit(np.concatenate([X_train, X_validate]), np.concatenate([Y_train, Y_validate]))
        Y_test_pred = final_model.predict(X_test)
        print("\n==========Attack Cat Scores for all features ==========")
        vulnerabilities = ["None", "Generic", "Fuzzers", "Exploits", "Dos", "Reconnaissance","Analysis","Shellcode","Backdoors","Worms"]
        print(f"{classification_report(Y_test_pred,Y_test,target_names=vulnerabilities, zero_division=0)}")
        end_time = time.time()
        print_elapsed_time(start_time, end_time)


    bks_trainning_data = training_data
    bks_test_data = test_data
    bks_validation_data = validation_data
    RFE_attack_cat_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl', 'service', 'Sload', 'stcpb', 'smeansz',
                        'dmeansz', 'Ltime', 'Sintpkt', 'synack', 'ct_srv_dst']
    RFE_Label_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl', 'Sload', 'Dload', 'dmeansz', 'res_bdy_len', 'Sjit',
                   'Djit', 'Stime', 'Ltime', 'Sintpkt']
    #bks_trainning_data, bks_test_data, bks_validation_data = RFE.rfe_model(training_data, test_data, validation_data, target)
    #bks_trainning_data, bks_test_data, bks_validation_data = SKB.skb(training_data, test_data, validation_data, target)

    Y_bks_train = bks_trainning_data[target]
    X_bks_train = bks_trainning_data.drop(['Label', 'attack_cat'], axis=1)
    Y_bks_test = bks_test_data[target]
    X_bks_test = bks_test_data.drop(['Label', 'attack_cat'], axis=1)
    Y_bks_val = bks_validation_data[target]
    X_bks_val = bks_validation_data.drop(['Label', 'attack_cat'], axis=1)



    if target == "Label":
        scaler = StandardScaler()
        X_train = scaler.fit_transform(X_bks_train[RFE_Label_X])
        X_test = scaler.transform(X_bks_test[RFE_Label_X])
        X_validate = scaler.transform(X_bks_val[RFE_Label_X])
        # Retrain the model with the best hyperparameter on the combined training and validation set
        final_model = KNeighborsClassifier(n_neighbors=5, weights='distance', metric='manhattan', n_jobs=5)
        final_model.fit(np.concatenate([X_train, X_validate]), np.concatenate([Y_bks_train, Y_bks_val]))
        Y_test_pred = final_model.predict(X_test)
        print("\n==========Label Scores for SELECTED features ==========")
        print(f"{classification_report(Y_test_pred,Y_test, labels=[0,1], zero_division=0)}")
        end_time = time.time()
        print_elapsed_time(start_time, end_time)
        with open(f'KNN_{target}.pkl', 'wb') as file:
            pickle.dump(final_model, file)
    elif target == "attack_cat":
        scaler = StandardScaler()
        X_train = scaler.fit_transform(X_bks_train[RFE_attack_cat_X])
        X_test = scaler.transform(X_bks_test[RFE_attack_cat_X])
        X_validate = scaler.transform(X_bks_val[RFE_attack_cat_X])
        # Retrain the model with the best hyperparameter on the combined training and validation set
        final_model = KNeighborsClassifier(n_neighbors=5, weights='distance', metric='manhattan', n_jobs=5)
        final_model.fit(np.concatenate([X_train, X_validate]), np.concatenate([Y_bks_train, Y_bks_val]))
        Y_test_pred = final_model.predict(X_test)
        print("\n==========Attack Cat Scores for SELECTED features ==========")
        vulnerabilities = ["None", "Generic", "Fuzzers", "Exploits", "Dos", "Reconnaissance","Analysis","Shellcode","Backdoors","Worms"]
        print(f"{classification_report(Y_test_pred,Y_test,target_names=vulnerabilities, zero_division=0)}")
        end_time_attack_cat = time.time()
        print_elapsed_time(start_time, end_time)
        with open(f'KNN_{target}.pkl', 'wb') as file:
            pickle.dump(final_model, file)

