#include "pch.h"
#include "CppUnitTest.h"
#include "../map/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {
	TEST_CLASS(UnitTest1) {
	public:
		
		TEST_METHOD(ConstructorTest) {
			Map<int, string> map1;
			Assert::IsTrue(!map1.begin(), L"Fail in constructor: map1's begin iterator must be nullptr");
			Assert::IsTrue(!map1.end(), L"Fail in constructor: map1's end iterator must be nullptr ");
			Assert::IsTrue(map1.get_size() == 0, L"Fail in constructor: map1's size must be 0");
		}

		TEST_METHOD(CopyConstructorTest) {
			Map<int, string> map1;
			map1.insert(2, "apple");
			map1.insert(3, "peach");
			map1.insert(1, "coconut");
			Map<int, string> map2(map1);
			Assert::IsTrue(map1.get_size() == map2.get_size(), L"Fail in copy-constructor: map1 and map2 doesn't have the same size");
			Assert::IsTrue(map1.begin()->key == map2.begin()->key, L"Fail in copy-constructor: map1 and map2 doesn't have the same first element");
			Assert::IsTrue(map1.next(map1.begin())->key == map2.next(map2.begin())->key, L"Fail in copy-constructor: map1 and map2 doesn't have the same second element");
			Assert::IsTrue(map1.end()->key == map2.end()->key, L"Fail in copy-constructor: map1 and map2 doesn't have the same end element");
		}

		TEST_METHOD(FindKeyMethodTest) {
			Map<int, string> map1;
			for (int i = 0; i < 10; i++) {
				map1.insert(i, to_string(i + 10));
			}
			Assert::IsTrue(map1.find(5), L"Fail in find-key-method: 5 is in map, but method return false");
			Assert::IsTrue(map1.find(1), L"Fail in find-key-method: 1 is in map, but method return false");
			Assert::IsTrue(map1.find(9), L"Fail in find-key-method: 9 is in map, but method return false");
			Assert::IsTrue(!map1.find(15), L"Fail in find-key-method: 15 is not in map, but method return true");
			Assert::IsTrue(!map1.find(112), L"Fail in find-key-method: 112 is not in map, but method return true");
			Assert::IsTrue(!map1.find(150), L"Fail in find-key-method: 150 is not in map, but method return true");
		}

		TEST_METHOD(BeginIteratorTest) {
			Map<int, string> map1; 
			Assert::IsTrue(!map1.begin(), L"Fail in begin-iterator: map1.begin() must be nullptr, but map1.begin() is not nullptr");
			map1.insert(1, "apple"); 
			Assert::IsTrue(map1.begin(), L"Fail in begin-iterator: map1.begin() must not be nullptr, but map1.begin() is nullptr");
			Assert::IsTrue(map1.begin()->key == 1, L"Fail in begin-iterator: map1.begin()->key must be one, but map1.begin()->key is not 1");
			Assert::IsTrue(map1.begin()->value == "apple", L"Fail in begin-iterator: map1.begin()->value must be \"apple\", but map1.begin()->value is not \"apple\"");
			map1.insert(2, "coconut");
			Assert::IsTrue(map1.begin(), L"Fail in begin-iterator: map1.begin() must not be nullptr, but map1.begin() is nullptr");
			Assert::IsTrue(map1.begin()->key == 1, L"Fail in begin-iterator: map1.begin()->key must be one, but map1.begin()->key is not 1");
			Assert::IsTrue(map1.begin()->value == "apple", L"Fail in begin-iterator: map1.begin()->value must be \"apple\", but map1.begin()->value is not \"apple\"");
		}

		TEST_METHOD(EndIteratorTest) {
			Map<int, string> map1;
			Assert::IsTrue(!map1.end(), L"Fail in end-iterator: map1.end() must be nullptr, but map1.end() is not nullptr");
			map1.insert(1, "apple");
			Assert::IsTrue(map1.end(), L"Fail in end-iterator: map1.end() must not be nullptr, but map1.end() is nullptr");
			Assert::IsTrue(map1.end()->key == 1, L"Fail in end-iterator: map1.end()->key must be one, but map1.end()->key is not 1");
			Assert::IsTrue(map1.end()->value == "apple", L"Fail in end-iterator: map1.end()->value must be \"apple\", but map1.end()->value is not \"apple\"");
			map1.insert(2, "coconut");
			Assert::IsTrue(map1.end(), L"Fail in end-iterator: map1.end() must not be nullptr, but map1.end() is nullptr");
			Assert::IsTrue(map1.end()->key == 2, L"Fail in end-iterator: map1.end()->key must be 2, but map1.begin()->key is not 2");
			Assert::IsTrue(map1.end()->value == "coconut", L"Fail in end-iterator: map1.end()->value must be \"coconut\", but map1.end()->value is not \"coconut\"");
		}

		TEST_METHOD(ClearTest) {
			Map<int, string> map;
			map.clear();
			Assert::IsTrue(map.get_size() == 0, L"Fail in ClearTest: size must be 0");
			Assert::IsTrue(!map.begin(), L"Fail in ClearTest: map.begin() is not nullptr");
			Assert::IsTrue(!map.end(), L"Fail in ClearTest: map.end() is not nullptr");
			map.insert(1, "apple");
			map.clear(); 
			Assert::IsTrue(map.get_size() == 0, L"Fail in ClearTest: size must be 0");
			Assert::IsTrue(!map.begin(), L"Fail in ClearTest: map.begin() is not nullptr");
			Assert::IsTrue(!map.end(), L"Fail in ClearTest: map.end() is not nullptr");
		}

		TEST_METHOD(InsertTest) {
			Map<int, string> map;
			Assert::IsTrue(map.get_size() == 0, L"map's size must be 0");
			Assert::IsTrue(!map.begin(), L"Fail in ClearTest: map.begin() is not nullptr");
			map.insert(2, "coconut");
			auto tmp = map.begin();
			Assert::IsTrue(map.get_size() == 1, L"map's size must be 2");
			Assert::IsTrue(map.begin()->key == 2, L"Fail in ClearTest: map.begin()->key must be 2");
			Assert::IsTrue(map.begin()->value == "coconut", L"Fail in ClearTest: map.begin()->value must be \"coconut\"");
			map.insert(1, "apple");
			Assert::IsTrue(map.get_size() == 2, L"map's size must be 2");
			map.insert(3, "peach");
			Assert::IsTrue(map.get_size() == 3, L"map's size must be 3");
			Assert::IsTrue(tmp->left->key == 1, L"map.begin()->left->key must be 1");
			Assert::IsTrue(tmp->right->key == 3, L"map.begin()->right->key must be 3");
			map.insert(3, "apple");
			Assert::IsTrue(map.get_size() == 3, L"map's size must be 3"); 
		}

		TEST_METHOD(EraseTest) {
			Map<int, string> map;
			map.insert(2, "coconut");
			auto tmp = map.begin(); 
			map.insert(1, "apple");
			map.insert(3, "peach");
			Assert::IsTrue(map.get_size() == 3, L"map's size must be 3");
			map.erase(3);
			Assert::IsTrue(map.get_size() == 2, L"map's size must be 2");
			Assert::IsTrue(tmp->right == nullptr, L"map.begin()->right must be nullptr");
			Assert::IsTrue(tmp->left != nullptr, L"map.begin()->left must not be nullptr");
		}

		TEST_METHOD(UserTypeType) {
			Map<int, Student> map;
			Assert::IsTrue(map.get_size() == 0, L"map's size must be 0");
			Assert::IsTrue(!map.begin(), L"Fail in ClearTest: map.begin() is not nullptr");
			map.insert(2, Student());
			auto tmp = map.begin(); 
			Assert::IsTrue(map.get_size() == 1, L"map's size must be 2");
			Assert::IsTrue(map.begin()->key == 2, L"Fail in ClearTest: map.begin()->key must be 2");
			map.insert(1, Student(4)); 
			Assert::IsTrue(map.get_size() == 2, L"map's size must be 2");
			map.insert(3, Student(5));
			Assert::IsTrue(map.get_size() == 3, L"map's size must be 3");
			Assert::IsTrue(tmp->left->key == 1, L"tmp->left->key must be 1");
			Assert::IsTrue(tmp->right->key == 3, L"tmp->right->key must be 3");
			map.insert(3, Student(6));
			Assert::IsTrue(map.get_size() == 3, L"map's size must be 3");
		}
	};
}
