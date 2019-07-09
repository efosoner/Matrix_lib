#include "Matrix.h"
using namespace std;

void header() {
	cout << "Version: 0.02.\n";
	cout << "Created by Dawid Galka as a first ever project for Univeristy of Zielona Gora.\n";
	cout << "GitHub link: https://github.com/efosoner\n";
	cout << "Use command /help for more informations.\n\n";
	cout << "-------------------------------------------------------------------------------------------------------\n";
}

int interface_main() {

	unordered_map<string, Matrix> matrixMap;

	while (1) {
		string command;
		cin >> command;

		if (command == "/help") {

			cout << "\n/add - adds matrix" << endl << endl;
			cout << "/show (matrix_id) - shows matrix" << endl << endl;
			cout << "/unit (matrix_id) (size_of_matrix) - creates unit matrix" << endl << endl;
			cout << "/rev (matrix_id) - reverses matrix" << endl << endl;
			cout << "/det (matrix_id) - calculates determinant" << endl << endl;
			cout << "/tp (matrix_id) - transposes matrix" << endl << endl;
			cout << "/pow (matrix_id) (power) - calculates power of matrix" << endl << endl;
			cout << "/elementary simple operations on matrices" << endl << endl;
			cout << "usage: (matrix_a) (operator) (matrix_b)" << endl << endl;
			cout << "/variable simple operations on single matrix" << endl << endl;
			cout << "usage: (matrix_a) (operator) (variable)" << endl << endl;
			cout << "/search (matrix_id) (variable)" << endl << endl;
			cout << "/clean - clears command line" << endl;
			cout << "-------------------------------------------------------------------------------------------------------\n" << endl;
		}

		else if (command == "/add") {
			int sizeWidth, sizeHeight;
			string key;
			cout << "Insert matrix Id: \n";
			cin >> key;
			while (key == "all") {
				cout << "Invalid_argument\n";
				cin >> key;
			}
			cout << "Insert number of variables: \n";
			cin >> sizeWidth;
			cout << "Insert number of equations: \n";
			cin >> sizeHeight;

			Matrix a(sizeHeight, sizeWidth);
			cin >> a;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cout << "Invalid_argument\n";
			}
			else matrixMap.insert({ key, a });
		}

		else if (command == "/show") {
			string key;
			cin >> key;
			if (key == "all") {
				for (const auto &pair : matrixMap) {
					cout << endl << pair.first;
				}
				cout << endl;
				cin >> key;
			}
			else {
				auto search = matrixMap.find((string)key);
				if (search != matrixMap.end()) {
					cout << endl << key << ":\n";
					cout << matrixMap.at(key);
				}
				else cout << "Invalid_argument\n";
			}
		}

		else if (command == "/unit") {
			string key;
			int size;
			cin >> key;
			cin >> size;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cout << "Invalid_argument\n";
			}
			else {
				Matrix a(size);
				a = a.UnitMatrix(size);
				matrixMap.insert({ key, a });
			}
		}

		else if (command == "/det") {
			string key;
			cin >> key;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cout << endl;
				cout << matrixMap.at(key) << " det:\n";
				cout << det(matrixMap.at(key), matrixMap.at(key).getHeight());
				cout << endl;
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/rev") {
			string key;
			cin >> key;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cout << endl;
				cout << key << " reversed:\n";
				cout << reverse(matrixMap.at(key));
				cout << endl;
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/pow") {
			string key;
			int power;
			cin >> key;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cin >> power;
				cout << endl;
				cout << key << " powered to " << power << ":\n";
				cout << matrixMap.at(key).Power(power);
				cout << endl;
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/tp") {
			string key;
			cin >> key;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				cout << endl;
				cout << key << " transposed to:\n";
				matrixMap.at(key) = matrixMap.at(key).Transposition();
				cout << matrixMap.at(key);
				cout << endl;
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/elementary") {
			string key_a;
			string key_b;
			char var_operator;

			cin >> key_a;
			cin >> var_operator;
			cin >> key_b;

			auto search = matrixMap.find((string)key_a);
			if (search != matrixMap.end()) {
				search = matrixMap.find((string)key_b);

				if (search != matrixMap.end()) {

					if (var_operator == '+') {
						cout << endl;
						cout << "Sum equals:\n";
						cout << matrixMap.at(key_a) + matrixMap.at(key_b);
						cout << endl;
					}

					else if (var_operator == '*') {
						cout << endl;
						cout << "Product equals:\n";
						cout << matrixMap.at(key_a) * matrixMap.at(key_b);
						cout << endl;
					}

					else if (var_operator == '-') {
						cout << endl;
						cout << "Difference equals:\n";
						cout << matrixMap.at(key_a) - matrixMap.at(key_b);
						cout << endl;
					}

					else cout << "Unknown_operator\n";
				}
				else cout << "Invalid_argument\n";
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/variable") {
			string key_a;
			double variable;
			char var_operator;

			cin >> key_a;
			cin >> var_operator;
			cin >> variable;

			auto search = matrixMap.find((string)key_a);
			if (search != matrixMap.end()) {

				if (var_operator == '+') {
					cout << endl;
					cout << "Sum equals:\n";
					cout << matrixMap.at(key_a) + variable;
					cout << endl;
				}

				else if (var_operator == '*') {
					cout << endl;
					cout << "Product equals:\n";
					cout << matrixMap.at(key_a) * variable;
					cout << endl;
				}

				else if (var_operator == '-') {
					cout << endl;
					cout << "Difference equals:\n";
					cout << matrixMap.at(key_a) - variable;
					cout << endl;
				}

				else cout << "Unknown_operator\n";
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/search") {
			string key;
			cin >> key;
			double variable;
			cin >> variable;

			auto search = matrixMap.find((string)key);
			if (search != matrixMap.end()) {
				matrixMap.at(key).n2search(variable);
			}
			else cout << "Invalid_argument\n";
		}

		else if (command == "/exit") {
			return EXIT_SUCCESS;
		}

		else if (command == "/clean") {
			system("cls");
			header();
		}

		else cout << "Unknown_command\n";

	}
}

int main() {

	header();
	interface_main();

	system("pause");
	return EXIT_SUCCESS;
}