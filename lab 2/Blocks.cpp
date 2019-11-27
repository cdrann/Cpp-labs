//
// Created by Admin on 29.10.2019.
//

#include "Blocks.h"

BlockFactory& BlockFactory::Instance() {
    static BlockFactory factory;
    return factory;
}

void BlockFactory::RegisterMaker(const std::string &key, IBlockMaker *maker) {
    makers[key] = maker;
}

IBlock* BlockFactory::Create(std::list<std::string>& blockDescription) {
    std::string key = *(blockDescription.begin());
    auto i = makers.find(key);

    try {
        if (i == makers.end())
            throw std::invalid_argument("No such command.");
    } catch (std::exception &err) {
        std::cerr << "Error:" << err.what() << std::endl;
        return nullptr;
    }
    IBlockMaker* maker = i->second;
    return maker->Create(blockDescription);
}


static BlockMaker<Readfile> makerReadfile("readfile");

Readfile::Readfile(std::list<std::string>& arguments) {
    auto it = arguments.begin();
    std::advance(it, 1);
    if (it != arguments.end())
        finName = *it;
}

std::vector<std::string> Readfile::DoCommand(std::vector<std::string>& txt) {
    text = txt;
    fin.open(finName);

    if (!fin.is_open()) {
        throw std::ios_base::failure("File doesn't exist.");
    }

    text.clear();
    std::string curr_line;
    while (getline(fin, curr_line)) {
        text.push_back(curr_line);
    }

    fin.close();
    return text;
}

Type_block Readfile::ReturnBlockType() {
    return in;
}


static BlockMaker<Writefile> makeWritefile("writefile");

Writefile::Writefile(std::list<std::string> &arguments) {
    auto it = arguments.begin();
    std::advance(it, 1);
    if (it != arguments.end())
        foutName = *it;
}

std::vector<std::string> Writefile::DoCommand(std::vector<std::string>& txt) {
    text = txt;
    fout.open(foutName);

    if (!fout.is_open())
        throw std::ios_base::failure("File doesn't exist.");

    for (const std::string& i : text) {
        fout << i << std::endl;
    }

    fout.close();
    return text;
}

Type_block Writefile::ReturnBlockType() {
    return out;
}


static BlockMaker<Grep> makeGrep("grep");

Grep::Grep(std::list<std::string> &args) {
    auto it = args.begin();
    std::advance(it, 1);
    if (it != args.end()) {
        argumentGrep = *it;
    }
}

std::vector<std::string> Grep::DoCommand(std::vector<std::string>& txt) {
    text = txt;

    if (argumentGrep.empty())
        throw std::invalid_argument("No argument for command grep.");

    std::vector<std::string> newText;
    for (auto & i : text) {
        int itPos = i.find(argumentGrep, 0);
        if (itPos > 0) {
            newText.push_back(i);
        }
    }
    text.resize(newText.size());
    text = newText;
    return text;
}

Type_block Grep::ReturnBlockType() {
    return in_out;
}


static BlockMaker<Sort> makerSort("sort");

Sort::Sort(std::list<std::string> &arguments) {}

std::vector<std::string> Sort::DoCommand(std::vector<std::string>& txt) {
    text = txt;
    std::sort(text.begin(), text.end());
    return text;
}

Type_block Sort::ReturnBlockType() {
    return in_out;
}


static BlockMaker<Replace> makerReplace("replace");

Replace::Replace(std::list<std::string> &args) {
    auto it = args.begin();
    std::advance(it, 1);
    if (it != args.end())
        firstReplaceArg = *it;

    std::advance(it, 1);
    if (it != args.end())
        secondReplaceArg = *it;

}

std::vector<std::string> Replace::DoCommand(std::vector<std::string>& txt) {
    text = txt;

    if (firstReplaceArg.empty() || secondReplaceArg.empty())
        throw std::invalid_argument("Not enough argument for replace.");

    for (std::string& i : text) {
        int itPos = i.find(firstReplaceArg, 0);
        while (itPos != std::string::npos) {
            i.replace(itPos, firstReplaceArg.size(), secondReplaceArg);
            itPos = i.find(firstReplaceArg, itPos);
        }
    }
    return text;
}

Type_block Replace::ReturnBlockType() {
    return in_out;
}


static BlockMaker<Dump> makerDump("dump");

Dump::Dump(std::list<std::string>& args) {
    auto it = args.begin();
    std::advance(it, 1);
    if (it != args.end())
        logName = *it;

}

std::vector<std::string> Dump::DoCommand(std::vector<std::string>& txt) {
    text = txt;
    flog.open(logName);

    if (!flog.is_open())
        throw std::ios_base::failure("File doesn't exist.");

    for (const std::string& i : text) {
        flog << i << std::endl;
    }

    flog.close();
    return text;
}

Type_block Dump::ReturnBlockType() {
    return in_out;
}
