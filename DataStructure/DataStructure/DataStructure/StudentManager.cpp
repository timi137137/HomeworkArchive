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
	double excellentPercent; // 优秀（>=90）
	double goodPercent; // 良好（80-89）
	double mediumPercent; // 中等（70-79）
	double passPercent; // 及格（60-69）
	double failPercent; // 不及格（<60）
};
struct SearchResult {
	bool isFound;
	char id[10];
	int score;
};


void readFromFile(SeqList<Student>& list, const char* filename) {
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "无法打开数据文档，请检查路径或文档是否正确" << endl;
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

	cout << "输入学号: ";
	cin >> student.id;
	cout << "输入学生姓名: ";
	cin >> student.name;
	cout << "输入学生成绩: ";
	cin >> student.score;
	cout << "输入要添加的位置: ";
	cin >> position;
	list.insertList(position, student);
}

void deleteStudent(SeqList<Student>& list) {
	Student* student = new Student();
	int position;

	cout << "输入要移除的位置: ";
	cin >> position;
	list.deleteList(position, student);
	cout << endl;
	cout << "被移除的记录为：" << student->name << endl;
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

	cout << "排序后的学生信息：" << endl;
	for (int i = 0; i < list.getLength(); ++i) {
		cout << "学号：" << list.getElement(i).id << ", 姓名：" << list.getElement(i).name << ", 成绩：" << list.getElement(i).score << endl;
	}
}

int main() {
	SeqList<Student> list(100);
	readFromFile(list, "data.txt");

	int choice;

	while (true) {
		system("cls");

		cout << "请选择操作：" << endl;
		cout << "1. 输出所有数据" << endl;
		cout << "2. 添加学生信息" << endl;
		cout << "3. 删除学生信息" << endl;
		cout << "4. 显示成绩信息" << endl;
		cout << "5. 显示平均成绩" << endl;
		cout << "6. 查找学生信息" << endl;
		cout << "7. 按成绩排序学生信息" << endl;
		cout << "8. 退出" << endl;
		cout << "请输入您的选择：";

		cin >> choice;
		switch (choice) {
		case 1:
			list.printList("output.txt");
			cout << "输出完毕，请查看文件" << endl;
			break;
		case 2:
			addStudent(list);
			break;
		case 3:
			deleteStudent(list);
			break;
		case 4: {
			ScoreInfo scoreInfo = getScoreInfo(list);

			cout << "最高分: " << scoreInfo.highestScore << endl;
			for (const Student& stu : scoreInfo.highestScorers) {
				cout << "学生: " << stu.name << " (" << stu.id << ")" << endl;
			}
			cout << "最低分: " << scoreInfo.lowestScore << endl;
			for (const Student& stu : scoreInfo.lowestScorers) {
				cout << "学生: " << stu.name << " (" << stu.id << ")" << endl;
			}
			break;
		}
		case 5:
			ScoreStatistics stats = calcScoreStatistics(list);
			cout << fixed << setprecision(2);
			cout << "平均分: " << stats.average << endl;
			cout << "优秀百分比: " << stats.excellentPercent << "%" << endl;
			cout << "良好百分比: " << stats.goodPercent << "%" << endl;
			cout << "中等百分比: " << stats.mediumPercent << "%" << endl;
			cout << "及格百分比: " << stats.passPercent << "%" << endl;
			cout << "不及格百分比: " << stats.failPercent << "%" << endl;
			break;
		case 6: {
			string nameToFind{};
			cout << "请输入要查找的学生姓名：";
			cin >> nameToFind;
			SearchResult result = findStudentByName(list, nameToFind);
			if (result.isFound) {
				cout << "找到学生。学号：" << result.id << "，成绩：" << result.score
					<< endl;
			}
			else {
				cout << "未找到学生：" << nameToFind << endl;
			}
			break;
		}
		case 7:
			bubbleSortByScore(list); 
			cout << "已按成绩排序学生信息。" << endl;
			break;
		case 8:
			return 0;
		default:
			cout << "无效选择，请重新输入" << endl;
		}

		system("pause");
	}
}