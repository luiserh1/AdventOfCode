PRIORITARY_0 = -1
PRIORITARY_1 = 1


def print_data(data, num):
	num_numbers = len(data)
	num = min(num, num_numbers)
	print("First {} (from a total of {}) binary numbers:".format(num, num_numbers))
	for code in data[:num]:
		print(code)


def get_processed_input(input_path, data):
	"""The data is a square matrix. Each row is a binary number"""
	with open(input_path, "rt") as f:
		input = f.read()
		lines = input.split("\n")
		data += [[int(n) for n in word] for word in lines]
		print_data(data, 10)


def binary_to_decimal(binary):
	dec = 0
	exp = 0
	for digit in binary[::-1]:
		if digit:
			dec += 2**exp
		exp += 1
	return dec


def get_epsilon_gamma_rates(data, priority):
	"""The priority determines the "winner" when there are the same amount of 0s and 1s"""
	num_numbers = len(data)
	sums = [num for num in data[0]]
	for number in data[1:]:
		for i in range(len(number)):
			sums[i] += number[i]
	gamma_rate = [0 for i in range(len(sums))]
	epsilon_rate = [0 for i in range(len(sums))]
	for i in range(len(sums)):
		digit = sums[i]
		if (len(data) % 2 != 0 and digit > num_numbers / 2) or (len(data) % 2 == 0 and digit > num_numbers / 2 + priority):
			gamma_rate[i] += 1
		else:
			epsilon_rate[i] += 1
	return epsilon_rate, gamma_rate


def part_a(data):
	epsilon_rate, gamma_rate = get_epsilon_gamma_rates(data, PRIORITARY_0)
	e_rate_dec = binary_to_decimal(epsilon_rate)
	g_rate_dec = binary_to_decimal(gamma_rate)
	return e_rate_dec * g_rate_dec, epsilon_rate, gamma_rate


def part_b(data):
	# Soft copies
	o2_generator_rating_candidates = [binary_num for binary_num in data]
	co2_scrubber_rating_candidates = [binary_num for binary_num in data]

	for i in range(len(data[0])):
		epsilon_rate, gamma_rate = get_epsilon_gamma_rates(o2_generator_rating_candidates, PRIORITARY_1)
		o2_generator_rating_candidates = [binary_num for binary_num in o2_generator_rating_candidates if binary_num[i] == epsilon_rate[i]]
		if len(o2_generator_rating_candidates) < 2:
			break
	for i in range(len(data[0])):
		epsilon_rate, gamma_rate = get_epsilon_gamma_rates(co2_scrubber_rating_candidates, PRIORITARY_0)
		co2_scrubber_rating_candidates = [binary_num for binary_num in co2_scrubber_rating_candidates if binary_num[i] == gamma_rate[i]]
		if len(co2_scrubber_rating_candidates) < 2:
			break

	o2_generator_rating = binary_to_decimal(o2_generator_rating_candidates[0])
	co2_scrubber_rating = binary_to_decimal(co2_scrubber_rating_candidates[0])
	return o2_generator_rating * co2_scrubber_rating, o2_generator_rating_candidates[0], co2_scrubber_rating_candidates[0]


def main():
	data = []
	input_path = "input.txt"
	get_processed_input(input_path, data)

	sol_a, epsilon_rate, gamma_rate = part_a(data)
	print("======================\nSOL A: [{}] is the result of multiplying {} ({}) of epsilon rate and {} ({}) of gamma rate".format(
		sol_a, epsilon_rate, binary_to_decimal(epsilon_rate),  gamma_rate, binary_to_decimal(gamma_rate)))

	sol_b, o2_generator_rating, co2_scrubber_rating = part_b(data)
	print("======================\nSOL B: [{}] is the result of multiplying {} ({}) of oxygen generator rating by {} ({})".format(
		sol_b, o2_generator_rating, binary_to_decimal(o2_generator_rating),  co2_scrubber_rating,
		binary_to_decimal(co2_scrubber_rating)), " of CO2 scrubber rating")


if __name__=="__main__":
	main()