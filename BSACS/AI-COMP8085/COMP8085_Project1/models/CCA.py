from sklearn.feature_selection import SelectKBest, mutual_info_classif

def correlation_coefficient(training_data, test_data, validate_data, target):
    print("executing corr coef.")
    exclude_cols = [0, 2]
    if (target == "Label") :
        exclude_cols.append(47)
    else:
        exclude_cols.append(48)


    print("dropping cols...")
    numeric_cols = training_data.drop(training_data.columns[exclude_cols], axis=1)

    print("Making corr matrix")
    correlation_matrix = numeric_cols.corr()
    print("Sorting with target")
    correlation_with_target = correlation_matrix[target].sort_values(ascending=False)

    threshold = 0.1
    print(f"Displaying feature correlations:")
    selected_features_corr = correlation_with_target[abs(correlation_with_target) > threshold].index.tolist()
    print(correlation_with_target)
    print(f"Number of features with abs correlation greater than (c = {threshold}): {len(selected_features_corr)}")
    print(selected_features_corr)

    if (target == "Label"):
        selected_features_corr.append("attack_cat")
    else:
        selected_features_corr.append("Label")

    print("Saving to CSV...")
    train_df = training_data[selected_features_corr]
    train_df.to_csv('data/CCA-train-bin.csv', index=False)

    test_df = test_data[selected_features_corr]
    test_df.to_csv('data/CCA-test-bin.csv', index=False)

    validate_df = validate_data[selected_features_corr]
    validate_df.to_csv('data/CCA-validate-bin.csv', index=False)

    return train_df, test_df, validate_df
    
