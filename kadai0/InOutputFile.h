//━━━━━━━━━━━━━━━━━━━━━━━
// ファイル名　　：InOutputFile.h
// 概要　　　　　：外部ファイルを読み込み・書き込みクラス
// 作成者　　　　：20CU0314 ゴコケン
// 更新内容　　　：2021/10/28 作成
//━━━━━━━━━━━━━━━━━━━━━━━
#pragma once
#include <fstream>
#include <vector>
#include "Define.h"

struct Data;

class InOutputFile
{
public:
    // ファイルの読み込みと書き込み
    void OutputAllDataToFile(const char* _path);                // 今持っているデータをすべてファイルに書き込みます（ファイルにある元のデータは消される）
    bool LoadFileProcess(const char* _path);                    // 外部ファイルのデータを読み込む処理をまとめたメソッド

    void AddDataToFile(const char* _path, std::vector<Data>& _data); // データをファイルに追加する（上書きしない）

    // データ管理用
    void SortByLargest();                                       // 今持っているデータを大きい順で並び変え（大ー＞小）
    Data SeachData(std::string _dataName);                      // データの名前でデータを検索する
    int  GetDataIdxByName(std::string _dataName);
    Data GetData(const int _idx);                               // 要素番号でデータを取得する
    void AddData(Data& _data);                                  // データを追加する
    std::vector<Data> GetAllData();                                  // 全部データを取得する
    void CleanData();                                           // 外部ファイルを開く
    void UpdateData(int& _idx, Data& _newData);

private:
    bool OpenFile(const char* _path);                           // 開いているファイルのデータを読み込む
    void LoadData();                                            // 保存しているデータを削除

private:
    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
    std::vector<Data> m_data;
};