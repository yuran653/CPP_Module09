# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    input_txt_generator.py                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 19:10:06 by jgoldste          #+#    #+#              #
#    Updated: 2023/11/29 19:10:18 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import random

# Function to generate correct lines
def generate_correct_line():
    date = f"2023-{random.randint(1, 12):02d}-{random.randint(1, 28):02d}"
    value = random.uniform(0, 1000)
    return f"{date} | {value:.2f}"

# Function to generate incorrect lines based on scenarios
def generate_incorrect_line(scenario):
    if scenario == 'Negative number':
        return f"2023-01-01 | -{random.uniform(1, 1000):.2f}"
    elif scenario == 'Invalid date format':
        return f"Dec-01-2023 | {random.uniform(1, 1000):.2f}"
    elif scenario == 'Excessively large number':
        return f"2023-01-01 | {random.uniform(1e10, 1e15):.2f}"
    else:
        return "Invalid scenario"

# Generate 70 correct lines
correct_lines = [generate_correct_line() for _ in range(70)]

# Generate 30 incorrect lines (6 lines per scenario)
incorrect_lines = []
error_scenarios = ['Negative number', 'Invalid date format', 'Excessively large number']

for scenario in error_scenarios:
    incorrect_lines.extend([generate_incorrect_line(scenario) for _ in range(6)])

# Mix correct and incorrect lines
all_lines = correct_lines + incorrect_lines
random.shuffle(all_lines)

# Print the content to 'input.txt'
with open('input.txt', 'w') as file:
    file.write('\n'.join(all_lines))

# Print the number of lines in the file
print(f"Number of lines in 'input.txt': {len(all_lines)}")
