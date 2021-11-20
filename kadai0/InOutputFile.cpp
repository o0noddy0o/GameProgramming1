//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：InOutputFile.cpp
// 概要　　　　　：外部ファイルを読み込み・書き込みクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/10/28 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#include "CActionGameApp.h"
#include "InOutputFile.h"

//━━━━━━━━━━━━━━━━━━━━━━━
// 今持っているデータをすべてファイルに書き込みます（ファイルにある元のデータは消される）
// 引数１：ファイルのパス
//━━━━━━━━━━━━━━━━━━━━━━━
void InOutputFile::OutputAllDataToFile(const char* _path)
{
    // ファイルを開く
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

    // ファイルを閉じる
    m_outputFile.close();
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 外部ファイルのデータを読み込む処理をまとめたメソッド
// 引数１：ファイルのパス
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// データをファイルに追加する（上書きしない）
// 引数１：ファイルのパス
// 引数２：追加するデータの配列
//━━━━━━━━━━━━━━━━━━━━━━━
void InOutputFile::AddDataToFile(const char* _path, vector<Data>& _data)
{
    // ファイルを開く
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

//━━━━━━━━━━━━━━━━━━━━━━━
// 今持っているデータを大きい順で並び変え（大ー＞小）
// ※int型とfloat型のデータしか使えません
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// データの名前でデータを検索する
// 引数１：検索したいデータの名前
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// データの名前でデータの番号を検索する
// 引数１：検索したいデータの名前
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// 要素番号でデータを取得する
// 引数１：取得したいデータの要素番号
//━━━━━━━━━━━━━━━━━━━━━━━
Data InOutputFile::GetData(const int _idx)
{
    return m_data[_idx];
}

//━━━━━━━━━━━━━━━━━━━━━━━
// データを追加する
// 引数１：追加するデータ
//━━━━━━━━━━━━━━━━━━━━━━━
void InOutputFile::AddData(Data& _data)
{
    m_data.push_back(_data);
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 全部データを取得する
//━━━━━━━━━━━━━━━━━━━━━━━
vector<Data> InOutputFile::GetAllData()
{
    return m_data;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 外部ファイルを開く
// 引数１：ファイルのパス
//━━━━━━━━━━━━━━━━━━━━━━━
bool InOutputFile::OpenFile(const char* _path)
{
    if (!m_inputFile.is_open())
    {
        m_inputFile.open(_path, ios::in);
        if (m_inputFile.fail())
        {
            cout << "読み込み失敗！！" << endl;
            return false;
        }
        return true;
    }
    return false;
}

//━━━━━━━━━━━━━━━━━━━━━━━
// 開いているファイルのデータを読み込む
//━━━━━━━━━━━━━━━━━━━━━━━
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

//━━━━━━━━━━━━━━━━━━━━━━━
// 保存しているデータを削除
//━━━━━━━━━━━━━━━━━━━━━━━
void InOutputFile::CleanData()
{
    m_data.clear();
}

void InOutputFile::UpdateData(int& _idx, Data& _newData)
{
    if (_idx >= m_data.size())return;

    m_data[_idx] = _newData;
}