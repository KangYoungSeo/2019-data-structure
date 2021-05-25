#include <string>
#include<iostream>
#include<list>
#include<map>

using namespace std;

struct Person {

	string name;
	Person *tmp;

	list<Person *> k;
	Person() { tmp = NULL; }

};

map<string, Person*> H; //key(value를 가리키는 것), value(저장할 자료)

Person* ceo;

void Show_map( long count, Person * N ) {

	if (N == NULL) 
		return;
	else {

		for (long i = 1; i <= count; ++i)
			cout << '+';

		cout << N->name << endl;

		for (list<Person*>::iterator i = N->k.begin(); i != N->k.end(); ++i)
			Show_map(count + 1, *i);

	}

}

void Hire_people(string str1, string str2) {

	map<string, Person*>::iterator search_people = H.find(str1); 
		//map에 str1을 이름을 가진 사람을 찾음.

	if (search_people != H.end()) { //찾을 경우

		Person *tmp = H[str1];		
		Person *k = new Person();

		k->name = str2;
		k->tmp = tmp;

		tmp->k.push_back(k);

		H[str2] = k;

	}
	else //못 찾았을 경우
		cout << "해당이름을 가진 사람이 존재하지 않습니다. " << endl;
}

void Fire_people(string str) {
	
	map<string, Person*>::iterator FindIter = H.find(str); //map에 str이름을 가진 사람이 있는지 찾기

	if (FindIter != H.end()) { // str 이름을 가진 사람 찾을 경우 제거

		Person *k = H[str];
		Person *tmp = k->tmp;

		H.erase(str);

		while (k->k.size() != 0) {

			k->name = k->k.front()->name;
			H[k->name] = k;
			k = k->k.front();
		}

		k->tmp->k.remove(k);
		
		delete k;

		return;

	}
	else
		cout << "There is no person whose name is " << str << endl;


}


int main() {

	string str1, str2;
	string sub_s1 = ""; // ceo 이름 말고도 뒤에 다른 문장 쳤을떄 무시. ceo이름만 입력받기
	string fin = " ";

	long i;
	int get_ceo = false;

	if (get_ceo == false) {
	F:
		getline(cin, str1); // ceo 이름을 입력받습니다.

		int idx = str1.find(fin);	//idx를 받습니다.

		if (idx != -1) {
			cout << "Please input only CEO name" << endl;
			goto F;

		}
		else {
			ceo = new Person(); //ceo 객체를 선언
			H[str1] = ceo;
			ceo->name = str1;	//ceo 이름 저장.

			get_ceo = true;	//ceo 저장 true
		}
	}

	if (get_ceo == true) {

		while (cin >> str1) {

			if (str1 == "print" || str1 == "Print") {	//print입력

				Show_map(0, ceo);		//map 출력
				cout << "=============================" << endl;

			}
			else if (str1 == "fire" || str1 == "Fire") {	//fire입력

				cin >> str2; //해고할 사람이름 입력
				Fire_people(str2);	//해당 사람 찾기.
			}

			else if (str1 != "print" || str1 != "Print" || str1 != "fire" || str1 != "Fire") {

				map<string, Person*>::iterator FindIter = H.find(str1); //map에 str1이름을 가진 사람 탐색

				if (FindIter != H.end()) //찾았을경우
				{
					cin >> str2; // 코멘트 입력받기

					if (str2 == "hires") {
						cin >> str2; //고용할 사람이름 이력
						Hire_people(str1, str2);	//str1가 상사이고 str2가 부하직원임을 저장.
					}

				}
				else
					cout << "해당이름을 가진 사람이 없습니다." << endl;
			}
			else
				cout << "invaild command" << endl;
		}
	}
	return 0;
}