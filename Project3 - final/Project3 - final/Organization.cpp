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

map<string, Person*> H; //key(value�� ����Ű�� ��), value(������ �ڷ�)

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
		//map�� str1�� �̸��� ���� ����� ã��.

	if (search_people != H.end()) { //ã�� ���

		Person *tmp = H[str1];		
		Person *k = new Person();

		k->name = str2;
		k->tmp = tmp;

		tmp->k.push_back(k);

		H[str2] = k;

	}
	else //�� ã���� ���
		cout << "�ش��̸��� ���� ����� �������� �ʽ��ϴ�. " << endl;
}

void Fire_people(string str) {
	
	map<string, Person*>::iterator FindIter = H.find(str); //map�� str�̸��� ���� ����� �ִ��� ã��

	if (FindIter != H.end()) { // str �̸��� ���� ��� ã�� ��� ����

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
	string sub_s1 = ""; // ceo �̸� ���� �ڿ� �ٸ� ���� ������ ����. ceo�̸��� �Է¹ޱ�
	string fin = " ";

	long i;
	int get_ceo = false;

	if (get_ceo == false) {
	F:
		getline(cin, str1); // ceo �̸��� �Է¹޽��ϴ�.

		int idx = str1.find(fin);	//idx�� �޽��ϴ�.

		if (idx != -1) {
			cout << "Please input only CEO name" << endl;
			goto F;

		}
		else {
			ceo = new Person(); //ceo ��ü�� ����
			H[str1] = ceo;
			ceo->name = str1;	//ceo �̸� ����.

			get_ceo = true;	//ceo ���� true
		}
	}

	if (get_ceo == true) {

		while (cin >> str1) {

			if (str1 == "print" || str1 == "Print") {	//print�Է�

				Show_map(0, ceo);		//map ���
				cout << "=============================" << endl;

			}
			else if (str1 == "fire" || str1 == "Fire") {	//fire�Է�

				cin >> str2; //�ذ��� ����̸� �Է�
				Fire_people(str2);	//�ش� ��� ã��.
			}

			else if (str1 != "print" || str1 != "Print" || str1 != "fire" || str1 != "Fire") {

				map<string, Person*>::iterator FindIter = H.find(str1); //map�� str1�̸��� ���� ��� Ž��

				if (FindIter != H.end()) //ã�������
				{
					cin >> str2; // �ڸ�Ʈ �Է¹ޱ�

					if (str2 == "hires") {
						cin >> str2; //����� ����̸� �̷�
						Hire_people(str1, str2);	//str1�� ����̰� str2�� ������������ ����.
					}

				}
				else
					cout << "�ش��̸��� ���� ����� �����ϴ�." << endl;
			}
			else
				cout << "invaild command" << endl;
		}
	}
	return 0;
}