//����������������������������������������������
// �t�@�C�����@�@�FInOutputFile.cpp
// �T�v�@�@�@�@�@�F�O���t�@�C����ǂݍ��݁E�������݃N���X
// �쐬�ҁ@�@�@�@�F20CU0314 �S�R�P��
// �X�V���e�@�@�@�F2021/10/28 �쐬
//����������������������������������������������
#include "CActionGameApp.h"
#include "InOutputFile.h"

//����������������������������������������������
// �������Ă���f�[�^�����ׂăt�@�C���ɏ������݂܂��i�t�@�C���ɂ��錳�̃f�[�^�͏������j
// �����P�F�t�@�C���̃p�X
//����������������������������������������������
void InOutputFile::OutputAllDataToFile(const char* _path)
{
    // �t�@�C�����J��
    if (!m_outputFile.is_open())
    {
        m_outputFile.open(_path, ios::out | ios::trunc);
        if (m_outputFile.fail())
        {
            return;
        }
    }
    else
    {
        return;
    }

    for (unsigned int i = 0; i < m_data.size(); ++i)
    {
        m_outputFile << m_data[i].dataName << " " << m_data[i].dataType << " ";
        if (m_data[i].dataType == "f")
        {
            m_outputFile << m_data[i].fData << "\n" << "\n";
        }
        else if (m_data[i].dataType == "i")
        {
            m_outputFile << m_data[i].iData << "\n" << "\n";
        }
        else if (m_data[i].dataType == "i2")
        {
            m_outputFile << m_data[i].i2Data.x << " " << m_data[i].i2Data.y << "\n" << "\n";
        }
        else if (m_data[i].dataType == "f2")
        {
            m_outputFile << m_data[i].f2Data.x << " " << m_data[i].f2Data.y << "\n" << "\n";
        }
        else if (m_data[i].dataType == "f4")
        {
            m_outputFile << m_data[i].f4Data.x << " " << m_data[i].f4Data.y << " " 
                << m_data[i].f4Data.z << " " << m_data[i].f4Data.w << "\n" << "\n";
        }
    }

    // �t�@�C�������
    m_outputFile.close();
}

//����������������������������������������������
// �O���t�@�C���̃f�[�^��ǂݍ��ޏ������܂Ƃ߂����\�b�h
// �����P�F�t�@�C���̃p�X
//����������������������������������������������
bool InOutputFile::LoadFileProcess(const char* _path)
{
    if (OpenFile(_path))
    {
        LoadData();
        m_inputFile.close();
        return true;
    }
    else
    {
        return false;
    }
}

//����������������������������������������������
// �f�[�^���t�@�C���ɒǉ�����i�㏑�����Ȃ��j
// �����P�F�t�@�C���̃p�X
// �����Q�F�ǉ�����f�[�^�̔z��
//����������������������������������������������
void InOutputFile::AddDataToFile(const char* _path, vector<Data>& _data)
{
    // �t�@�C�����J��
    if (!m_outputFile.is_open())
    {
        m_outputFile.open(_path, ios::out | ios::app);
        if (m_outputFile.fail())
        {
            return;
        }
    }
    else
    {
        return;
    }


    for (unsigned int i = 0; i < _data.size(); ++i)
    {
        m_outputFile << _data[i].dataName << " " << _data[i].dataType << " ";
        if (_data[i].dataType == "f")
        {
            m_outputFile << _data[i].fData << "\n" << "\n";
        }
        else if (_data[i].dataType == "i")
        {
            m_outputFile << _data[i].iData << "\n" << "\n";
        }
    }

    m_outputFile.close();
}

//����������������������������������������������
// �������Ă���f�[�^��傫�����ŕ��ѕς��i��[�����j
// ��int�^��float�^�̃f�[�^�����g���܂���
//����������������������������������������������
void InOutputFile::SortByLargest()
{
    std::vector<Data> buf;

    while (m_data.size())
    {
        auto idx = m_data.begin();
        for (auto it = m_data.begin() + 1; it != m_data.end(); ++it)
        {
            if (*it > *idx)
            {
                idx = it;
            }
        }
        buf.push_back(*idx);
        m_data.erase(idx);
    }
    m_data = buf;
}

//����������������������������������������������
// �f�[�^�̖��O�Ńf�[�^����������
// �����P�F�����������f�[�^�̖��O
//����������������������������������������������
Data InOutputFile::SeachData(string _dataName)
{
    for (unsigned int i = 0; i < m_data.size(); ++i)
    {
        if (m_data[i].dataName == _dataName)
        {
            return m_data[i];
        }
    }
    return Data();
}

//����������������������������������������������
// �f�[�^�̖��O�Ńf�[�^�̔ԍ�����������
// �����P�F�����������f�[�^�̖��O
//����������������������������������������������
int InOutputFile::GetDataIdxByName(string _dataName)
{
    for (unsigned int i = 0; i < m_data.size(); ++i)
    {
        if (m_data[i].dataName == _dataName)
        {
            return (int)i;
        }
    }
    return -1;
}

//����������������������������������������������
// �v�f�ԍ��Ńf�[�^���擾����
// �����P�F�擾�������f�[�^�̗v�f�ԍ�
//����������������������������������������������
Data InOutputFile::GetData(const int _idx)
{
    return m_data[_idx];
}

//����������������������������������������������
// �f�[�^��ǉ�����
// �����P�F�ǉ�����f�[�^
//����������������������������������������������
void InOutputFile::AddData(Data& _data)
{
    m_data.push_back(_data);
}

//����������������������������������������������
// �S���f�[�^���擾����
//����������������������������������������������
vector<Data> InOutputFile::GetAllData()
{
    return m_data;
}

//����������������������������������������������
// �O���t�@�C�����J��
// �����P�F�t�@�C���̃p�X
//����������������������������������������������
bool InOutputFile::OpenFile(const char* _path)
{
    if (!m_inputFile.is_open())
    {
        m_inputFile.open(_path, ios::in);
        if (m_inputFile.fail())
        {
            cout << "�ǂݍ��ݎ��s�I�I" << endl;
            return false;
        }
        return true;
    }
    return false;
}

//����������������������������������������������
// �J���Ă���t�@�C���̃f�[�^��ǂݍ���
//����������������������������������������������
void InOutputFile::LoadData()
    {
        if (m_inputFile.is_open())
        {
            Data buf;
            while (m_inputFile >> buf.dataName)
            {
                m_inputFile >> buf.dataType;
                if (buf.dataType == "i")
                {
                    m_inputFile >> buf.iData;
                }
                else if (buf.dataType == "f")
                {
                    m_inputFile >> buf.fData;
                }
                else if (buf.dataType == "i2")
                {
                    m_inputFile >> buf.i2Data.x;
                    m_inputFile >> buf.i2Data.y;
                }
                else if (buf.dataType == "f2")
                {
                    m_inputFile >> buf.f2Data.x;
                    m_inputFile >> buf.f2Data.y;
                }
                else if (buf.dataType == "f4")
                {
                    m_inputFile >> buf.f4Data.x;
                    m_inputFile >> buf.f4Data.y;
                    m_inputFile >> buf.f4Data.z;
                    m_inputFile >> buf.f4Data.w;
                }
                m_data.push_back(buf);
            }
        }
    }

//����������������������������������������������
// �ۑ����Ă���f�[�^���폜
//����������������������������������������������
void InOutputFile::CleanData()
{
    m_data.clear();
}

void InOutputFile::UpdateData(int& _idx, Data& _newData)
{
    if (_idx >= m_data.size())return;

    m_data[_idx] = _newData;
}