from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.svm import SVC
from sklearn.metrics import classification_report, accuracy_score
from models.CCA import *
from models.RFE import *
import pickle

def SVM(training_data, test_data, validate_data, target):
    print("initializing targets")

    param_grid = {
        'C': [ 1, 10, 100, 1000],
        'kernel':['rbf']
    }

    targets = ["attack_cat", "Label"]
    RFE_attack_cat_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl','service', 'Sload', 'stcpb', 'smeansz', 'dmeansz', 'Ltime', 'Sintpkt','synack', 'ct_srv_dst']
    RFE_Label_X = ['sport', 'dsport', 'sbytes', 'dbytes', 'sttl', 'Sload', 'Dload', 'dmeansz', 'res_bdy_len', 'Sjit', 'Djit', 'Stime', 'Ltime', 'Sintpkt']
                
    #train, test, validate = rfe_model(training_data, test_data, validate_data, target)

    sample1 = training_data.sample(n=15000)
    sample2 = validate_data.sample(n=5000)

    y_train = sample1[target]
    y_test = sample2[target]

    X_train= []
    X_test= []

    print("Dropping targets from X dataframe...")
    if  (target == "Label"):
        X_train = sample1[RFE_Label_X]
        X_test = sample2[RFE_Label_X]
    else:
        X_train = sample1[RFE_attack_cat_X]
        X_test = sample2[RFE_attack_cat_X]

    print("Creating and applying scaler...")
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)

    print("Grid searching for best parameters...")
    grid_search = GridSearchCV(SVC(), param_grid, scoring='f1_macro', cv=5)
    grid_search.fit(X_train_scaled, y_train)

    print("Predicting with best model... ")
    best_model = grid_search.best_estimator_
    y_pred = best_model.predict(X_test_scaled)


    #vulnerabilities = ["None", "Generic", "Fuzzers", "Exploits", "Dos", "Reconnaissance","Analysis","Shellcode","Backdoors","Worms"]
    if (target == "Label"):
        vulnerabilities = ["Normal", "Malicious"]
    print("Best parameters: ", grid_search.best_params_)
    print("Best f1 score:", grid_search.best_score_)
    print(f"Accuracy: {accuracy_score(y_test, y_pred)}")
    print(classification_report(y_test, y_pred, zero_division=0))
    
    with open(f'SVM_{target}.pkl','wb') as file:
        pickle.dump (best_model, file)
