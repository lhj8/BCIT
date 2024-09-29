import pandas as pd
import pickle
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report, accuracy_score
from sklearn.model_selection import StratifiedKFold
from models import RFE as rfe


def gbc_model(train_data, test_data, val_data, target):
    print("\nRunning GBC Classifier...\n")

    vulnerabilities = ["None", "Generic", "Fuzzers", "Exploits", "Dos",
                       "Reconnaissance", "Analysis", "Shellcode",
                       "Backdoors", "Worms"]

    # TODO: To run small sample to train the model and find best using
    #       Hyperparameter tuning
    #       This make runtime short using selected features from RFE
    targets = ["attack_cat", "Label"]

    vars_label = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl', 'Sload',
                  'Dload', 'dmeansz', 'res_bdy_len', 'Sjit', 'Djit', 'Stime',
                  'Ltime', 'Sintpkt']

    vars_attack_cat = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl',
                       'service', 'Sload', 'stcpb', 'smeansz', 'dmeansz',
                       'Ltime', 'Sintpkt', 'synack', 'ct_srv_dst']

    # TODO: Hyperparameter tuning
    param_grid = {
        'n_estimators': [5, 10, 20],
        'learning_rate': [0.1, 0.3, 0.5],
        'max_depth': [3, 4, 5]
    }

    ip_feature = ['srcip', 'dstip']
    for ip in ip_feature:
        train_data[ip] = pd.factorize(train_data[ip])[0]
        test_data[ip] = pd.factorize(test_data[ip])[0]
        val_data[ip] = pd.factorize(val_data[ip])[0]

    # TODO: Can modify number of samples
    sample1 = train_data.sample(n=60000)
    sample2 = val_data.sample(n=10000)

    y_train = sample1[target]
    y_test = sample2[target]

    x_train = sample1.drop(targets, axis=1)
    x_test = sample2.drop(targets, axis=1)

    if target == "Label":
        x_train = x_train[vars_label]
        x_test = x_test[vars_label]
    else:
        x_train = x_train[vars_attack_cat]
        x_test = x_test[vars_attack_cat]

    print("Grid searching for best parameters...")
    cv = StratifiedKFold(n_splits=3)
    grid_search = GridSearchCV(GradientBoostingClassifier(),
                               param_grid,
                               scoring='f1_macro',
                               cv=cv)

    grid_search.fit(x_train, y_train)

    print("Predicting with best model... ")
    best_model = grid_search.best_estimator_
    y_pred = best_model.predict(x_test)

    print("Best parameters: ", grid_search.best_params_)
    print("Best f1 score:", grid_search.best_score_)
    print(f"Accuracy: {accuracy_score(y_test, y_pred)}")
    if target == 'Label':
        print(classification_report(y_test, y_pred))
    else:
        print(classification_report(y_test, y_pred,
                                    target_names=vulnerabilities,
                                    zero_division=0))

    with open(f'GBC_{target}.pkl', 'wb') as file:
        pickle.dump(best_model, file)

    # TODO: Running entire data set from feature selection to classifier.
    #       This will show the result of using classifier with all features and
    #       the selected features.
    #       < To use this comment out below and comment above >
    # Call feature selected .csv using RFE
    # ft_train_data, ft_test_data, ft_val_data = rfe.rfe_model(train_data,
    #                                                          test_data,
    #                                                          val_data,
    #                                                          target)
    #
    # print("\nProcessing all feature - " + target)
    # x_all_train = train_data.drop(['attack_cat', 'Label'], axis=1)
    # y_all_train = train_data[target]
    # x_all_test = test_data.drop(['attack_cat', 'Label'], axis=1)
    # y_all_test = test_data[target]
    #
    # if target == 'Label':
    #     # Default: max_depth=3, learning_rate=0.1
    #     classifier_all = GradientBoostingClassifier(n_estimators=20,
    #                                                 learning_rate=0.5,
    #                                                 max_depth=3)
    # else:
    #     classifier_all = GradientBoostingClassifier(learning_rate=0.1,
    #                                                 max_depth=3)
    # classifier_all.fit(x_all_train, y_all_train)
    # pred_all = classifier_all.predict(x_all_test)
    # if target == 'Label':
    #     print(classification_report(y_all_test, pred_all))
    # else:
    #     print(classification_report(y_all_test,
    #                                 pred_all,
    #                                 target_names=vulnerabilities))
    # val_score_all = accuracy_score(y_all_test, pred_all)
    # print("Accuracy score: ", val_score_all)
    #
    # # Selected Feature
    # print("\nProcessing selected feature - " + target)
    # x_ft_train = ft_train_data.drop(['attack_cat', 'Label'], axis=1)
    # y_ft_train = ft_train_data[target]
    # x_ft_test = ft_test_data.drop(['attack_cat', 'Label'], axis=1)
    # y_ft_test = ft_test_data[target]
    #
    # if target == 'Label':
    #     # Default: max_depth=3, learning_rate=0.1
    #     classifier_ft = GradientBoostingClassifier(n_estimators=20,
    #                                                learning_rate=0.5,
    #                                                max_depth=3)
    # else:
    #     classifier_ft = GradientBoostingClassifier(learning_rate=0.1,
    #                                                max_depth=3)
    #
    # classifier_ft.fit(x_ft_train, y_ft_train)
    # pred_ft = classifier_ft.predict(x_ft_test)
    #
    # if target == 'Label':
    #     print(classification_report(y_ft_test, pred_ft))
    # else:
    #     print(classification_report(y_ft_test,
    #                                 pred_ft,
    #                                 target_names=vulnerabilities,
    #                                 zero_division=0))
    #
    # val_score_ft = accuracy_score(y_ft_test, pred_ft)
    # print("Accuracy score: ", val_score_ft)
