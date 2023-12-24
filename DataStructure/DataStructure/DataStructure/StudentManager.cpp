#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include "SequenceList.cpp"

using namespace std;

typedef struct {
	char id[10];
	char name[20];
	int score;
} Student;
struct ScoreInfo {
	int highestScore;
	vector<Student> highestScorers;
	int lowestScore;
	vector<Student> lowestScorers;
};
struct ScoreStatistics {
	double average;
	double excellentPercent; // ���㣨>=90��
	double goodPercent; // ���ã�80-89��
	double mediumPercent; // �еȣ�70-79��
	double passPercent; // ����60-69��
	double failPercent; // ������<60��
};
struct SearchResult {
	bool isFound;
	char id[10];
	int score;
};


void readFromFile(SeqList<Student>& list, const char* filename) {
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "�޷��������ĵ�������·�����ĵ��Ƿ���ȷ" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		istringstream matrix(line);
		if (line.empty()) continue;

		Student student;
		matrix >> student.id >> student.name >> student.score;
		list.appendList(student);
	}
	file.close();
}

void addStudent(SeqList<Student>& list) {
	Student student;
	int position;

	cout << "����ѧ��: ";
	cin >> student.id;
	cout << "����ѧ������: ";
	cin >> student.name;
	cout << "����ѧ���ɼ�: ";
	cin >> student.score;
	cout << "����Ҫ��ӵ�λ��: ";
	cin >> position;
	list.insertList(position, student);
}

void deleteStudent(SeqList<Student>& list) {
	Student* student = new Student();
	int position;

	cout << "����Ҫ�Ƴ���λ��: ";
	cin >> position;
	list.deleteList(position, student);
	cout << endl;
	cout << "���Ƴ��ļ�¼Ϊ��" << student->name << endl;
}

ScoreInfo getScoreInfo(SeqList<Student>& list) {
	ScoreInfo info;

	info.highestScore = list.getElement(0).score;
	info.lowestScore = list.getElement(0).score;
	for (int i = 0; i < list.getLength(); ++i) {
		if (list.getElement(i).score > info.highestScore) {
			info.highestScore = list.getElement(i).score;
			info.highestScorers.clear();
			info.highestScorers.push_back(list.getElement(i));
		}
		else if (list.getElement(i).score == info.highestScore) {
			info.highestScorers.push_back(list.getElement(i));
		}
		if (list.getElement(i).score < info.lowestScore) {
			info.lowestScore = list.getElement(i).score;
			info.lowestScorers.clear();
			info.lowestScorers.push_back(list.getElement(i));
		}
		else if (list.getElement(i).score == info.lowestScore) {
			info.lowestScorers.push_back(list.getElement(i));
		}
	}
	return info;
}

ScoreStatistics calcScoreStatistics(SeqList<Student>& list) {
	ScoreStatistics stats = { 0, 0, 0, 0, 0, 0 };
	int countExcellent = 0, countGood = 0, countMedium = 0, countPass = 0,
		countFail = 0;

	int totalScore = 0;
	for (int i = 0; i < list.getLength(); ++i) {
		totalScore += list.getElement(i).score;
		if (list.getElement(i).score >= 90) {
			countExcellent++;
		}
		else if (list.getElement(i).score >= 80) {
			countGood++;
		}
		else if (list.getElement(i).score >= 70) {
			countMedium++;
		}
		else if (list.getElement(i).score >= 60) {
			countPass++;
		}
		else {
			countFail++;
		}
	}

	int length = list.getLength();

	stats.average = static_cast<double>(totalScore) / length;
	stats.excellentPercent = static_cast<double>(countExcellent) / length * 100;
	stats.goodPercent = static_cast<double>(countGood) / length * 100;
	stats.mediumPercent = static_cast<double>(countMedium) / length * 100;
	stats.passPercent = static_cast<double>(countPass) / length * 100;
	stats.failPercent = static_cast<double>(countFail) / length * 100;

	return stats;
}

SearchResult findStudentByName(SeqList<Student>& list, const string name) {
	SearchResult result = { false, "", 0 };
	for (int i = 0; i < list.getLength(); ++i) {
		if (name == list.getElement(i).name) {
			result.isFound = true;
			strcpy_s(result.id, sizeof(result.id), list.getElement(i).id);
			result.score = list.getElement(i).score;
			break;
		}
	}
	return result;
}

void bubbleSortByScore(SeqList<Student>& list) {
	for (int i = 0; i < list.getLength() - 1; i++) {
		for (int j = 0; j < list.getLength() - i - 1; j++) {
			if (list.getElement(j).score > list.getElement(j+1).score) {
				Student temp = list.getElement(j);
				list.getElement(j) = list.getElement(j+1);
				list.getElement(j+1) = temp;
			}
		}
	}

	cout << "������ѧ����Ϣ��" << endl;
	for (int i = 0; i < list.getLength(); ++i) {
		cout << "ѧ�ţ�" << list.getElement(i).id << ", ������" << list.getElement(i).name << ", �ɼ���" << list.getElement(i).score << endl;
	}
}

int main() {
	SeqList<Student> list(100);
	readFromFile(list, "data.txt");

	int choice;

	while (true) {
		system("cls");

		cout << "��ѡ�������" << endl;
		cout << "1. �����������" << endl;
		cout << "2. ���ѧ����Ϣ" << endl;
		cout << "3. ɾ��ѧ����Ϣ" << endl;
		cout << "4. ��ʾ�ɼ���Ϣ" << endl;
		cout << "5. ��ʾƽ���ɼ�" << endl;
		cout << "6. ����ѧ����Ϣ" << endl;
		cout << "7. ���ɼ�����ѧ����Ϣ" << endl;
		cout << "8. �˳�" << endl;
		cout << "����������ѡ��";

		cin >> choice;
		switch (choice) {
		case 1:
			list.printList("output.txt");
			cout << "�����ϣ���鿴�ļ�" << endl;
			break;
		case 2:
			addStudent(list);
			break;
		case 3:
			deleteStudent(list);
			break;
		case 4: {
			ScoreInfo scoreInfo = getScoreInfo(list);

			cout << "��߷�: " << scoreInfo.highestScore << endl;
			for (const Student& stu : scoreInfo.highestScorers) {
				cout << "ѧ��: " << stu.name << " (" << stu.id << ")" << endl;
			}
			cout << "��ͷ�: " << scoreInfo.lowestScore << endl;
			for (const Student& stu : scoreInfo.lowestScorers) {
				cout << "ѧ��: " << stu.name << " (" << stu.id << ")" << endl;
			}
			break;
		}
		case 5:
			ScoreStatistics stats = calcScoreStatistics(list);
			cout << fixed << setprecision(2);
			cout << "ƽ����: " << stats.average << endl;
			cout << "����ٷֱ�: " << stats.excellentPercent << "%" << endl;
			cout << "���ðٷֱ�: " << stats.goodPercent << "%" << endl;
			cout << "�еȰٷֱ�: " << stats.mediumPercent << "%" << endl;
			cout << "����ٷֱ�: " << stats.passPercent << "%" << endl;
			cout << "������ٷֱ�: " << stats.failPercent << "%" << endl;
			break;
		case 6: {
			string nameToFind{};
			cout << "������Ҫ���ҵ�ѧ��������";
			cin >> nameToFind;
			SearchResult result = findStudentByName(list, nameToFind);
			if (result.isFound) {
				cout << "�ҵ�ѧ����ѧ�ţ�" << result.id << "���ɼ���" << result.score
					<< endl;
			}
			else {
				cout << "δ�ҵ�ѧ����" << nameToFind << endl;
			}
			break;
		}
		case 7:
			bubbleSortByScore(list); 
			cout << "�Ѱ��ɼ�����ѧ����Ϣ��" << endl;
			break;
		case 8:
			return 0;
		default:
			cout << "��Чѡ������������" << endl;
		}

		system("pause");
	}
}