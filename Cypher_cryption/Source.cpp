#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
std::string encode(std::string, std::map<char, char>);
std::string decode(std::string, std::map<char, char>);

void generate_cypher(std::map<char, char>& cypher);

int main()
{
	std::map<char, char>cypher_table;


	generate_cypher(cypher_table);

	std::string input_text;
	std::cout << "Insert text you want to be encrypted" << std::endl;
	std::getline(std::cin, input_text);

	auto encrypted_text = encode(input_text, cypher_table);

	std::cout << "Encrypted text:" << encrypted_text << std::endl;

	std::cout << "Decoded text:" << decode(encrypted_text, cypher_table) << std::endl;

	return 0;
}

std::string encode(std::string in_string, std::map<char, char>cypher)
{
	std::string result = "";
	for (auto letter : in_string)
	{
		if (!isalpha(letter)) {
			result += letter;
			continue;
		}

		auto it = cypher.find(letter);

		result += it->second;
	}
	return result;
}
std::string decode(std::string lock_string, std::map  <char, char> cypher)
{


	std::string result = "";

	for (auto letter : lock_string)
	{

		if (!isalpha(letter)) {
			result += letter;
			continue;
		}

		for (auto pair : cypher)
		{
			if (pair.second == letter)
			{
				result += pair.first;
				break;
			}
		}

	}

	return result;
}

void generate_cypher(std::map<char, char>& cypher)
{
	srand(time(NULL));

	cypher.clear();

	std::set<char>left, right;
	//generate ABCD... vectors
	for (char c = 'A'; c <= 'Z'; c++)
	{
		left.insert(c);
		right.insert(c);
	}
	for (char c = 'a'; c <= 'z'; c++)
	{
		left.insert(c);
		right.insert(c);
	}
	//On random getting in cypher 
	while (left.size())//dokle god nije nula
	{
		auto random_index_left = rand() % left.size();
		//get that char from set
		char left_char = '0';
		int index = 0;
		for (auto c : left)
		{
			//Uzimamo index i random index i kad su isti to slovo ubacimo u lijevi dio tablice i izbrisemo ga jer nezelimo da se ponavlja
			if (index == random_index_left)
			{
				left_char = c;
				left.erase(c);
				break;//Napravi break i izade iz fora i neide na index++ jer ga je nasa pa netreba dalje traziti.
			}
			index++;
		}
		auto random_index_right = rand() % right.size();
		char right_char = '0';
		index = 0;
		for (auto c : right)
		{
			if (index == random_index_right)
			{
				right_char = c;
				right.erase(c);
				break;
			}
			index++;
		}

		cypher[left_char] = right_char;
	}
	//debug
	if (false)
		for (auto entry : cypher)
			std::cout << entry.first << "->" << entry.second << std::endl;
}

