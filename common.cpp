/*
 * File: common.cpp
 * Encoding: utf-8
 * Function: Fundamantal functions
 * Version: 1.5.0
 * Date: 2016-07-07
 * Author: QinZhengke
 * E-Mail: qinzhengke@qq.com
 *
 */

#include "common.h"

// Load the config file
int Config::load(std::string filePath)
{
    std::ifstream input;
    input.open(filePath);
    if(!input)
    {
        std::cout<<"Cannot find the config file!"<<std::endl;
        return -1;
    }

    std::string str;
    StringList strlst;
    while(!input.eof())
    {
        // Ignore the empty linesw
        std::getline(input,str);
        if(str == "")
            continue;
        else if(str.at(0) == '#')// Ignore the comment lines
            continue;
        strlst = splitString(str,"=");
        if(strlst.size() == 2)
        {
            argsName.push_back(strlst.at(0));
            argsValue.push_back(atof(strlst.at(1).c_str()));
        }
        if(argsName.size() == 0)
            std::cout<<"Warning, the config file does not contains any arguments!"<<std::endl;
    }
    return 1;
}

// Get the arguments by name
int Config::getArgFloat(std::string argName, float *value)
{
    for(int i=0;i<argsName.size();i++)
    {
        if(argName == argsName.at(i))
        {
            *value = argsValue.at(i);
            return 1;
        }
    }
    return -1;
}

// Get the arguments by name
int Config::getArgUchar(std::string argName, unsigned char *value)
{
    for(int i=0;i<argsName.size();i++)
    {
        if(argName == argsName.at(i))
        {
            *value = (unsigned char)argsValue.at(i);
            return 1;
        }
    }
    return -1;
}

// Get the arguments by name
int Config::getArgInt(std::string argName, int *value)
{
    for(int i=0;i<argsName.size();i++)
    {
        if(argName == argsName.at(i))
        {
            *value = (int)argsValue.at(i);
            return 1;
        }
    }
    return -1;
}


Pose::Pose(double x, double y, double z, double rx, double ry, double rz)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
}
