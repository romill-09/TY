import numpy as np
import pandas as pd

# Read the CSV file
file_path = './processed_food_coded1.csv'  # Relative path if the file is in the same directory as the script
df = pd.read_csv(file_path)

# Finding missing, null values and replacing with mean for numeric columns
numeric_columns = df.select_dtypes(include=['number']).columns
for column in numeric_columns:
    column_mean = df[column].mean()
    df[column].fillna(column_mean, inplace=True)

# Encoding categorical data
df['cuisine_encoded'], categories = pd.factorize(df['cuisine'])
category_dict = {i: category for i, category in enumerate(categories)}

# Normalizing the 'nutritional_check' column
def normalize_column(df, column_name):
    min_value = df[column_name].min()
    max_value = df[column_name].max()
    df[f'normalized_{column_name}'] = (df[column_name] - min_value) / (max_value - min_value)
    return df

df = normalize_column(df, 'nutritional_check')

# Discretizing the 'nutritional_check' column
def discretize_column(df, column_name, num_bins):
    bin_labels = ['Good', 'Moderate', 'Low']
    
    # Use pandas cut function to discretize the column
    df[f'discretized_{column_name}'] = pd.cut(df[column_name], bins = num_bins, labels=bin_labels)
    
    return df

num_bins = 3
df = discretize_column(df, 'normalized_nutritional_check', num_bins)



# Save the processed DataFrame to a new CSV file
output_file_path = './processed_food_coded1.csv'
df.to_csv(output_file_path, index=False)
print(f"Processed DataFrame saved to {output_file_path}")