#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<string>
using namespace std;
#define LEN 500

/**************************************************
	���ڳ��ȿɱ�������������� + λ��
**************************************************/


/*
	�����ļ��ṹ
*/
typedef struct File
{
	string name;//�ļ���
	float size;//�ļ���С
}File;

/*
	�����ļ������ṹ
*/
typedef struct Fat //file allocation table�ļ������
{
	string fileName; //�ļ���
	int indexBlock; //�������
}Fat;


/*
	��������ļ���С
*/
float randFileSize()
{
	//srand(time(seed));
	float fileSize = (rand() % 81 + 20)/10.0f;//���������СΪ2k��10k���ļ�
	return fileSize;
}

/*
	�洢�ļ�
*/
bool storageFile(int bitTable[],vector<Fat> &FAT, File file, int disk[][LEN])
{
	int n = ceil(file.size/2);//����ȡ��������ļ��洢��Ҫ�Ŀ����������������飩
	
	//����Ƿ����㹻�Ŀտ�����Ÿ��ļ�
	int i = 0;
	int k = 0;
	int index = -1;//������
	for (; i < LEN; i++) {
		if (bitTable[i] == 0) {
			k++;
			if (k == 1) {
				index = i;//����������
			}
			if (k == n + 1) {
				break;
			}
		}
	}
	//û���㹻�ռ�����Ÿ��ļ�
	if (k <= n) {
		return false;
	}
	//cout << "�����飺" << index <<endl;
	///////////////////////////////////////////////////////////////
	//  
	//	�����㹻�Ŀհ׿�����Ÿ��ļ��������������ڵ�һ���հ׿���
	//
	///////////////////////////////////////////////////////////////

	//�����ļ������
	Fat fat;
	fat.fileName = file.name;
	fat.indexBlock = index;
	FAT.push_back(fat);
	
	//����λ��
	bitTable[index] = 1;
	i = index + 1;//�����������һ��λ�ü���Ѱ�ҿհ׿�
	k = 0;//��¼ÿ�η����ĳ���
	int t = 0;
	//����λ���ҵ���ŵ�λ�ã����������飬����λ��
	for (int j = 0; j < n; j++) {
		
		if (bitTable[i] == 0) {
			if (k == 0) {//����һ���µķ�������¼����ʼ��
				disk[index][t++] = i;
			}
			k++;
			bitTable[i] = 1;//����λ��
		}
		else{
			if (k != 0) {//��� k!=0 ˵�����÷�����������¼�³���
				disk[index][t++] = k;
				//cout << "\t��ʼ�飺" << disk[index][t - 2] << "\t����: " << disk[index][t - 1] << endl;
				disk[index][t] = -1;//����һ����־
				k = 0;
			}
			j--;
		}
		i++;
	}
	disk[index][t++] = k;
	disk[index][t] = -1;
	//cout << "\t��ʼ�飺" << disk[index][t - 2] << "\t����: " << disk[index][t - 1] << endl << endl;
	return true;
}

int indexBlockOfFile(vector<Fat> FAT, string fileName)
{
	for (int i = 0; i < FAT.size(); i++) {
		if (FAT[i].fileName == fileName) {
			return FAT[i].indexBlock;
		}
	}
	return -1;//���� -1 ˵��û���ҵ�
}

/*
	ɾ���ļ�����λ��
*/
bool deleteFile(int bitTable[], vector<Fat> &FAT, string fileName, int disk[][LEN])
{
	//���ļ���������ҵ�������
	for (int i = 0; i < FAT.size(); i++) {
		if (FAT[i].fileName == fileName) {
			int index = FAT[i].indexBlock;
			int t = 0;
			while (disk[index][t] != -1) {
				int begin = disk[index][t];
				int len = disk[index][t + 1];
				for (int j = 0; j < len; j++) {
					bitTable[begin + j] = 0;
				}
				t += 2;
			}
			bitTable[index] = 0;
			vector<Fat>::iterator itr = FAT.begin()+i;
			FAT.erase(itr);
			return true;
		}
	}
	return false;
}

/*
	���������ʹ洢��λ��
*/
void outputIndexBlock(int disk[][LEN], vector<Fat> FAT, File file)
{
	string fileName = file.name;
	int size = file.size;
	cout << fileName << "\t��С��" << size << "k" << endl;
	for (int i = 0; i < FAT.size(); i++) {
		if (FAT[i].fileName == fileName) {
			int index = FAT[i].indexBlock;
			cout << "�����飺" << index << endl;
			int t = 0;
			while (disk[index][t] != -1) {
				int begin = disk[index][t];
				int len = disk[index][t + 1];
				cout << "\t��ʼ�飺" << begin << "\t���ȣ�" << len << endl;
				t += 2;
			}
			break;
		}
	}
}

/*
	��ӡ�հ׿�
*/
void outputFreeBlock(int bitTable[])
{
	cout << "���п�" << endl;
	for (int i = 0; i < LEN; i++) {
		if (bitTable[i] == 0) {
			cout << i << "\t";
		}
	}
	cout << endl;
}
int main()
{
	int bitTable[LEN] = { 0 };//λ��
	int disk[LEN][LEN] = { -1 };//����
	vector<Fat> FAT; //�ļ������

	//�������2k-10k���ļ�50��,������洢��������
	File file[50];
	string fileName;
	float fileSize;
	for (int i = 0; i < 50; i++) {
		fileName = to_string(i+1) + ".txt"; //�ļ���
		fileSize = randFileSize(); //��������ļ���С
		file[i].name = fileName;
		file[i].size = fileSize;
		//cout << fileName << " " << fileSize << "\t";
		//�洢���ļ�	
		if (storageFile(bitTable, FAT, file[i], disk)) {
			//cout << "�ɹ������ļ���" << file[i].name << "   ��С��" << file[i].size << "k" << endl;
			outputIndexBlock(disk, FAT, file[i]); cout << endl;
		}
	}

	//outputFreeBlock(bitTable);

	cout << "\n-------------------" << endl;
	//ɾ�� ����.txt
	for (int i = 1; i < 50; i += 2) {
		string fileName = to_string(i) + ".txt";
		if(!deleteFile(bitTable, FAT, fileName, disk))break;
		cout << "�ɹ�ɾ���ļ���" << fileName << endl;
	}

	cout << "\n-------------------" << endl;
	//outputFreeBlock(bitTable);
	//�´��� 5 ���ļ�
	File fileA, fileB, fileC, fileD, fileE;
	fileA.name = "A.txt";	fileA.size = 7;
	fileB.name = "B.txt";	fileB.size = 5;
	fileC.name = "C.txt"; 	fileC.size = 2;
	fileD.name = "D.txt"; 	fileD.size = 9;
	fileE.name = "E.txt"; 	fileE.size = 3.5;
	/*
	storageFile(bitTable, FAT, fileA, disk);
	storageFile(bitTable, FAT, fileB, disk);
	storageFile(bitTable, FAT, fileC, disk);
	storageFile(bitTable, FAT, fileD, disk);
	storageFile(bitTable, FAT, fileE, disk);
	*/
	if (storageFile(bitTable, FAT, fileA, disk)) {
		cout << "�ɹ������ļ���" << fileA.name << "   ��С��" << fileA.size << "k" << endl;
	}
	if (storageFile(bitTable, FAT, fileB, disk)) {
		cout << "�ɹ������ļ���" << fileB.name << "   ��С��" << fileB.size << "k" << endl;
	}
	if (storageFile(bitTable, FAT, fileC, disk)) {
		cout << "�ɹ������ļ���" << fileC.name << "   ��С��" << fileC.size << "k" << endl;
	}
	if (storageFile(bitTable, FAT, fileD, disk)) {
		cout << "�ɹ������ļ���" << fileD.name << "   ��С��" << fileD.size << "k" << endl;
	}
	if (storageFile(bitTable, FAT, fileE, disk)) {
		cout << "�ɹ������ļ���" << fileE.name << "   ��С��" << fileE.size << "k" << endl;
	}
	
	cout << "\n-------------------" << endl;
	//������ 5 ���ļ����ļ������
	cout << "�ļ��������:" << endl;
	/*
	cout << fileA.name << " ��������Ϊ: " << indexBlockOfFile(FAT, fileA.name) << endl;
	cout << fileB.name << " ��������Ϊ: " << indexBlockOfFile(FAT, fileB.name) << endl;
	cout << fileC.name << " ��������Ϊ: " << indexBlockOfFile(FAT, fileC.name) << endl;
	cout << fileD.name << " ��������Ϊ: " << indexBlockOfFile(FAT, fileD.name) << endl;
	cout << fileE.name << " ��������Ϊ: " << indexBlockOfFile(FAT, fileE.name) << endl;
	*/
	outputIndexBlock(disk, FAT, fileA); cout << endl;
	outputIndexBlock(disk, FAT, fileB); cout << endl;
	outputIndexBlock(disk, FAT, fileC); cout << endl;
	outputIndexBlock(disk, FAT, fileD); cout << endl;
	outputIndexBlock(disk, FAT, fileE);

	cout << "\n-------------------" << endl;
	//������п�
	outputFreeBlock(bitTable);

	system("pause");
	return 0;
}