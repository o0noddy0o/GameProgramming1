//����������������������������������������������
// �t�@�C�����@�@�FInOutputFile.h
// �T�v�@�@�@�@�@�F�O���t�@�C����ǂݍ��݁E�������݃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/10/28 �쐬
//����������������������������������������������
#pragma once
#include <fstream>
#include <vector>
#include "Define.h"

struct Data;

class InOutputFile
{
public:
    // �t�@�C���̓ǂݍ��݂Ə�������
    void OutputAllDataToFile(const char* _path);                // �������Ă���f�[�^�����ׂăt�@�C���ɏ������݂܂��i�t�@�C���ɂ��錳�̃f�[�^�͏������j
    bool LoadFileProcess(const char* _path);                    // �O���t�@�C���̃f�[�^��ǂݍ��ޏ������܂Ƃ߂����\�b�h

    void AddDataToFile(const char* _path, std::vector<Data>& _data); // �f�[�^���t�@�C���ɒǉ�����i�㏑�����Ȃ��j

    // �f�[�^�Ǘ��p
    void SortByLargest();                                       // �������Ă���f�[�^��傫�����ŕ��ѕς��i��[�����j
    Data SeachData(std::string _dataName);                      // �f�[�^�̖��O�Ńf�[�^����������
    int  GetDataIdxByName(std::string _dataName);
    Data GetData(const int _idx);                               // �v�f�ԍ��Ńf�[�^���擾����
    void AddData(Data& _data);                                  // �f�[�^��ǉ�����
    std::vector<Data> GetAllData();                                  // �S���f�[�^���擾����
    void CleanData();                                           // �O���t�@�C�����J��
    void UpdateData(int& _idx, Data& _newData);

private:
    bool OpenFile(const char* _path);                           // �J���Ă���t�@�C���̃f�[�^��ǂݍ���
    void LoadData();                                            // �ۑ����Ă���f�[�^���폜

private:
    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
    std::vector<Data> m_data;
};