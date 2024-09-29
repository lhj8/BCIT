import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from sklearn.feature_selection import f_regression, SelectKBest
from sklearn.preprocessing import StandardScaler


def skb(training_data, test_data, validation_data, target):

    X = training_data.drop(['srcip', 'dstip', 'Label', 'attack_cat'], axis=1)
    Y = training_data[target]

    # Standardize the features
    scaler = StandardScaler()
    X_std = scaler.fit_transform(X)

    # Select K Best features
    selector = SelectKBest(k=16)
    X_new = selector.fit_transform(X_std, Y)

    # Extract the selected feature names
    selected_indices = selector.get_support(indices=True)
    selected_features = X.columns[selected_indices]

    # Get the feature scores (ensuring to handle NaN scores)
    scores = selector.scores_
    scores = np.nan_to_num(scores)

    #Plotting feature scores
    plt.figure(figsize=(10, 6))
    plt.bar(range(len(X.columns)), scores, tick_label=X.columns)
    plt.xticks(rotation=90)
    plt.xlabel('Features')
    plt.ylabel('Scores')
    plt.title('Univariate Feature Selection: Feature Scores')
    plt.tight_layout()  # Adjust layout to make room for the rotated x-axis labels
    plt.show()

    print("Selected Features:")
    print(selected_features)

    selected_features = np.append(selected_features,['attack_cat', 'Label'])

    train_df = training_data[selected_features]
    train_df.to_csv('./data/BKS-train-bin.csv', index=False)

    test_df = test_data[selected_features]
    test_df.to_csv('./data/BKS-test-bin.csv', index=False)

    validate_df = validation_data[selected_features]
    validate_df.to_csv('./data/BKS-validate-bin.csv', index=False)

    return train_df, test_df, validate_df