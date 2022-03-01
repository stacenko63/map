#include <iostream>
#include <ostream>
#include <string>
#include <set>
using namespace std;


template <typename T1, typename T2>
struct Node {
	T1 key;
	T2 value;
	Node* left = nullptr;
	Node* right = nullptr;
};

template <typename T1, typename T2>
class Map {

private:
	Node<T1,T2>* root = nullptr;
	
	size_t size = 0;

	void print_node(Node<T1,T2>* root) const {
		if (root) {
			cout << root->key << " : " << root->value << "  ";
			if (root->left) print_node(root->left);
			if (root->right) print_node(root->right);
		}
	}

	pair<Node<T1,T2>*, Node<T1,T2>*> find_element(T1 key) const {
		if (size == 0) return pair<Node<T1, T2>*, Node<T1, T2>*>(nullptr, nullptr);
		if (root->key == key) return pair<Node<T1, T2>*, Node<T1, T2>*>(root, nullptr);
		Node<T1,T2>* tmp = root;
		Node<T1,T2>* tmpPrev = root;
		bool flag = false;
		while (true) {
			if (tmp->key == key) return pair<Node<T1, T2>*, Node<T1, T2>*>(tmp, tmpPrev);
			if (key > tmp->key) {
				if (!tmp->right) return pair<Node<T1, T2>*, Node<T1, T2>*>(nullptr, nullptr);
				if (flag) tmpPrev = tmp;
				else flag = true;
				tmp = tmp->right;
			}
			else {
				if (!tmp->left) return pair<Node<T1, T2>*, Node<T1, T2>*>(nullptr, nullptr);
				if (flag) tmpPrev = tmp;
				else flag = true;
				tmp = tmp->left;
			}
		}
		return pair<Node<T1, T2>*, Node<T1, T2>*>(nullptr, nullptr);
	}

	void copy(Node<T1,T2>* el, const Map<T1,T2>& map) { 
		insert(el->key, el->value);
		if (el->right) copy(el->right, map);
		if (el->left) copy(el->left, map);
	}

	void del(Node<T1,T2>* el) {
		if (size != 0) {
			if (el->right) del(el->right);
			if (el->left) del(el->left);
			delete el;
			size--;
		}
	}

public:

	size_t get_size() {
		return size;  
	}

	Node<T1,T2>* begin() { 
		if (size == 0) return nullptr;
		Node<T1,T2>* tmp = root;
		while (tmp->left != nullptr) tmp = tmp->left;
		return tmp;
	}

	Node<T1,T2>* next(Node<T1,T2>* node) const { 
		return node ? find_element(node->key).second : nullptr;
	}

	Node<T1,T2>* end() const {
		if (size == 0) return nullptr;
		Node<T1,T2>* tmp = root;
		while (tmp->right != nullptr) tmp = tmp->right;
		return tmp;
	}

	Map(const Map<T1,T2>& map) {
		copy(map.root, map);
	}

	void clear() {
		del(root);
	}

	~Map() {
		clear();
	}

	Map() {}

	void print() const {
		if (size == 0) throw "Error! You can't print empty set!";
		print_node(root);
	}

	bool insert(T1 key, T2 value) {
		if (find(key)) return false;
		Node<T1,T2>* newNode = new Node<T1,T2>;
		newNode->key = key;
		newNode->value = value;
		if (size == 0) {
			root = newNode;
			size++;
			return true;
		}
		Node<T1,T2>* tmp = root;
		while (true) {
			if (key > tmp->key) {
				if (!tmp->right) {
					tmp->right = newNode;
					size++;
					return true;
				}
				tmp = tmp->right;
			}
			else {
				if (!tmp->left) {
					tmp->left = newNode;
					size++;
					return true;
				}
				tmp = tmp->left;
			}
		}
		return false;
	}

	bool find(T1 key) const {
		return find_element(key).first;
	}

	bool erase(T1 key) {
		if (size == 0) return false;
		pair<Node<T1,T2>*, Node<T1,T2>*> tmp = find_element(key);
		if (!tmp.first) return false;
		if (!tmp.first->left && !tmp.first->right) {
			delete tmp.first;
			tmp.second->right = nullptr;
		}
		else if (tmp.first->left && !tmp.first->right) {
			bool flag = tmp.second->left && tmp.second->left->key == tmp.first->key;
			Node<T1,T2>* tmp2 = tmp.first;
			tmp.first = tmp.first->left;
			delete tmp2;
			if (flag) tmp.second->left = tmp.first;
			else tmp.second->right = tmp.first;
		}
		else if (!tmp.first->left && tmp.first->right) {
			bool flag = tmp.second->left && tmp.second->left->key == tmp.first->key;
			Node<T1,T2>* tmp2 = tmp.first;
			tmp.first = tmp.first->right;
			delete tmp2;
			if (flag) tmp.second->left = tmp.first;
			else tmp.second->right = tmp.first;
		}
		else if (tmp.first->left && tmp.first->right) {
			Node<T1,T2>* tmp2 = tmp.first->right;
			while (tmp2->left != nullptr) tmp2 = tmp2->left;
			pair<Node<T1,T2>*, Node<T1,T2>*> tmp3 = find_element(tmp2->key);
			bool flag = tmp2->key == tmp.first->right->key;
			T1 dataKey = tmp2->key;
			T2 dataValue = tmp2->value;
			delete tmp2;
			tmp.first->key = dataKey;
			tmp.first->value = dataValue; 
			if (flag) tmp3.second->right = nullptr;
			else tmp3.second->left = nullptr;
		}
		size--;
		return true;
	}


	Node<T1,T2>* find(const T1& key) {
		return find_element(key).first;
	}

	Node<T1,T2>* find(const T1& key) const {
		return find_element(key).first;
	}

	//void erase(Node<T1,T2>* pos) {
	//	if (pos) erase(pos->number);
	//}

};

struct Student {
	int averageMark = 3;

	Student() {

	}

	Student(int average_mark) : averageMark(average_mark) {}

	Student(const Student& other) {
		averageMark = other.averageMark;
	}

	Student& operator=(const Student& other) {
		averageMark = other.averageMark;
		return *this;
	}


};

bool operator>(const Student& lhs, const Student& rhs) {
	return lhs.averageMark > rhs.averageMark;
}

bool operator==(const Student& lhs, const Student& rhs) {
	return lhs.averageMark == rhs.averageMark;
}

ostream& operator<<(ostream& os, const Student& student) {
	os << student.averageMark;
	return os;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, Node<T1,T2>* node) {
	if (node) cout << node->key << " " << node->value;
	return out;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, Node<T1,T2> node) {
	cout << node.number << " ";
	return out;
}

void input_correctly_number(int& aa) {
	while (!(cin >> aa) || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Invalid value entered. Try again: ";
	}
}

void repeat_action(int& menu) {
	cout << "1 - Repeat this action\n";
	cout << "2 - Back to the main menu\n";
	cout << "Enter your choice: ";
	input_correctly_number(menu);
	while (menu < 1 || menu > 2) {
		cout << "This number is not in the menu. Repeat the input: ";
		input_correctly_number(menu);
	}
}

template<typename T1, typename T2>
void add(Map<T1,T2>& map) {
	int menu = 1;
	do {
		system("cls");
		int key = 1;
		string value = "";
		cout << "Enter the key: "; 
		input_correctly_number(key);
		cout << "Enter the value: ";
		cin >> value;
		map.insert(key, value);
		repeat_action(menu);
	} while (menu != 2);
}

template<typename T1, typename T2>
void del(Map<T1, T2>& map) {
	int menu = 1;
	do {
		int key = 1;
		system("cls");
		cout << "Enter the key you want to delete: ";
		input_correctly_number(key);
		map.erase(key);
		repeat_action(menu);
	} while (menu != 2);
}
template<typename T1, typename T2>
void find(Map<T1, T2>& map) {
	int menu = 1;
	do {
		int key = 1;
		system("cls");
		cout << "Enter the key you want to find: ";
		input_correctly_number(key);
		if (map.find(key)) cout << "Your map contains this key\n";
		else cout << "Your map doesn't contain this key\n";
		repeat_action(menu);
	} while (menu != 2);
}

template<typename T1, typename T2>
void print(Map<T1, T2>& map) {
	int menu = 1;
	do {
		system("cls");
		cout << "\n";
		map.print();
		cout << "\n";
		repeat_action(menu);
	} while (menu != 2);
}

int main() {
	//Map<int, string> map; 
	//int menu = 1;
	//do {
	//	system("cls");
	//	cout << "1 - Add an item to the map\n";
	//	cout << "2 - Delete an element from the dictionary\n";
	//	cout << "3 - Find an element in the dictionary\n";
	//	cout << "4 - Print the map\n";
	//	cout << "Enter your choice: "; 
	//	input_correctly_number(menu);
	//	while (menu < 0 || menu > 4) {
	//		cout << "This number is not in the menu. Repeat the input: ";
	//		input_correctly_number(menu);
	//	}
	//	int key = 0;
	//	string value = ""; 
	//	if (menu == 1) add(map);
	//	else if (menu == 2) del(map);
	//	else if (menu == 3) find(map);
	//	else if (menu == 4) print(map);
	//} while (menu != 0);
	Map<int, string> map;
	map.insert(2, "coconut");
	auto tmp = map.begin();
	map.insert(1, "apple");
	map.insert(3, "peach");
	cout << (map.get_size() == 3) << "\n";
	map.erase(3);
	cout << (map.get_size() == 2) << "\n";
	cout << (tmp->right == nullptr) << "\n";
	cout << (tmp->left != nullptr) << "\n";
	map.erase(1);
	cout << (map.get_size() == 1) << "\n";
	cout << (tmp->right == nullptr) << "\n";
	cout << (tmp->left == nullptr) << "\n";
}