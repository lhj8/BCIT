import pandas as pd


def preprocess_data(df):
    """
    Preprocess the given DataFrame by applying a series of cleaning and formatting steps.
    Parameters: df (pandas.DataFrame)
    Returns: df (The preprocessed DataFrame)
    """

    # Fill `attack_cat` to 'normal'
    df = process_attack_cat(df)

    # Process port
    df = process_port(df)

    # Fill empty value of 'ct_flw_http_mthd' and 'is_ftp_login' to 0
    df = process_http_login(df)

    # Fill empty value of 'ct_ftp_cmd' to 0 and change data type to float 64
    df = process_cmd(df)

    # Factorize 'proto', 'state', 'service', 'and attack_cat'
    df = process_factorization(df)

    # Change data type to string for 'srcip' and 'dstip'
    df = process_stringify(df)

    return df


def process_attack_cat(df):
    df['attack_cat'] = df['attack_cat'].str.strip()
    # Standardize the category names
    df['attack_cat'] = df['attack_cat'].replace({'Backdoor': 'Backdoors'})
    df['attack_cat'] = df.attack_cat.fillna(value='normal').apply(
        lambda x: x.strip().lower())
    return df


def process_http_login(df):
    # Handle data conversion where the column may contain non-numeric values
    df['ct_flw_http_mthd'] = pd.to_numeric(df['ct_flw_http_mthd'], errors='coerce')
    df['ct_flw_http_mthd'] = df['ct_flw_http_mthd'].fillna(0)
    df['ct_flw_http_mthd'] = df['ct_flw_http_mthd'].astype(int)

    df['is_ftp_login'] = pd.to_numeric(df['is_ftp_login'], errors='coerce')
    df['is_ftp_login'] = df['is_ftp_login'].fillna(0)
    df['is_ftp_login'] = df['is_ftp_login'].astype(int)

    return df


def process_cmd(df):
    # Handle data conversion where the column may contain non-numeric values
    df['ct_ftp_cmd'] = pd.to_numeric(df['ct_ftp_cmd'], errors='coerce')
    df['ct_ftp_cmd'] = df['ct_ftp_cmd'].fillna(0)

    # Change data type to float64
    df['ct_ftp_cmd'] = df['ct_ftp_cmd'].astype(int)

    return df


def process_factorization(df):
    need_factorization = ['proto', 'state', 'service', 'attack_cat']
    df['service'] = df['service'].replace('-', 'unknown')
    # Factorize - Convert features to numerical format
    for feature in need_factorization:
        df[feature] = pd.factorize(df[feature])[0]

    return df


def process_stringify(df):
    need_string = ['srcip', 'dstip']

    for feature in need_string:
        df[feature] = pd.to_numeric(df[feature], errors='coerce').fillna(0)
        # Pandas support "string" after ver 1.0.0
        df[feature] = df[feature].astype('string')

    return df


def process_port(df):
    # Change port starting with '0x' to decimal
    df['sport'] = df['sport'].apply(hex_to_dec)
    df['dsport'] = df['dsport'].apply(hex_to_dec)

    # Change the value is 538989345 to 65535 of  'sport' and 'dsport'
    df['sport'] = df['sport'].replace('538989345', '65535')
    df['dsport'] = df['dsport'].replace('538989345', '65535')

    # Change the value is '-' to '0' of  'sport' and 'dsport'
    df['sport'] = df['sport'].replace('-', '0')
    df['dsport'] = df['dsport'].replace('-', '0')

    # Change data type to int64
    df['sport'] = df['sport'].astype(int)
    df['dsport'] = df['dsport'].astype(int)

    return df


def hex_to_dec(port):
    if isinstance(port, str) and port.startswith('0x'):
        return int(port, 16)
    else:
        return port

