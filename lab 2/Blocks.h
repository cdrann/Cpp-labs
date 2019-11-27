//
// Created by Admin on 29.10.2019.
//

#ifndef LAB2_BLOCKS_H
#define LAB2_BLOCKS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <stdexcept>
#include <algorithm>

enum Type_block {
    in, //reading only
    out, //writing only
    in_out //reading & writing
};

class IBlock {
public:
    virtual std::vector<std::string> DoCommand(std::vector<std::string>& some_text) = 0;
    virtual Type_block ReturnBlockType() = 0;
    virtual ~IBlock() = default;
};

class IBlockMaker {
public:
    virtual IBlock* Create(std::list<std::string>& block_description) = 0;
    virtual ~IBlockMaker() = default;
};

//Singleton which implements Factory
class BlockFactory {
public:
    void RegisterMaker(const std::string& key, IBlockMaker * maker);
    static BlockFactory& Instance();
    IBlock* Create(std::list<std::string>& blockDescription);
private:
    std::map<std::string, IBlockMaker*> makers;
};

template <typename T> class BlockMaker : public IBlockMaker {
public:
    BlockMaker(const std::string& key) {
        BlockFactory::Instance().RegisterMaker(key, this);
    }
    IBlock* Create(std::list<std::string>& block_description) override {
        return new T(block_description);
    }
};

class Readfile : public IBlock {
public:
    Readfile(std::list<std::string>& arguments);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::string finName;
    std::ifstream fin;
    std::vector<std::string> text;
};

class Writefile : public IBlock {
public:
    Writefile(std::list<std::string>& arguments);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::string foutName;
    std::ofstream fout;
    std::vector<std::string> text;
};

class Grep : public IBlock {
public:
    Grep(std::list<std::string>& args);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::string argumentGrep;
    std::vector<std::string> text;
};

class Replace : public IBlock {
public:
    Replace(std::list<std::string>& args);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::string firstReplaceArg;
    std::string secondReplaceArg;
    std::vector<std::string> text;
};

class Sort : public IBlock {
public:
    Sort(std::list<std::string>& arguments);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::vector<std::string> text;
};

class Dump : public IBlock {
public:
    Dump(std::list<std::string>& args);
    std::vector<std::string> DoCommand(std::vector<std::string>& txt) override;
    Type_block ReturnBlockType() override;
private:
    std::string logName;
    std::ofstream flog;
    std::vector<std::string> text;
};

#endif //LAB2_BLOCKS_H
