/*
 * File: common.h
 * Encoding: utf-8
 * Function: Fundamantal functions
 * Version: 1.5.0
 * Date: 2016-07-07
 * Author: QinZhengke
 * E-Mail: qinzhengke@qq.com
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sstream>
#include <fstream>

#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QObject>

// informative macro
#define IN
#define OUT

typedef std::vector<std::string> StringList;

// Splite the string $strSrc by the sub-string $s
inline StringList splitString(std::string strSrc, std::string s)
{
    int pos = 0;
    StringList slstOut;
    while(!strSrc.empty())
    {
        pos = strSrc.find(s);
        if(-1 == pos){
            slstOut.push_back(strSrc);
            return  slstOut;
        }
        slstOut.push_back(strSrc.substr(0,pos));
        strSrc = strSrc.substr(pos+s.size(),strSrc.size());
    }
}

// Config file class
class Config
{
public:
    // Load the config file
    int load(std::string filePath);
    // Get the arguments by name
    int getArgFloat(std::string argName, float *value);
    int getArgUchar(std::string argName, unsigned char *value);
    int getArgInt(std::string argName, int *value);

private:
    // Store the name of the arguments
    StringList argsName;
    // Store the value of the arguments
    std::vector<float> argsValue;
};

class Pose
{
public:
    Pose(double x, double y, double z, double rx, double ry, double rz);
    Pose(){}
    double x,y,z;
    double rx,ry,rz;

};

class Move
{
public:

    // Move type: MOVJ means moving base on joint, MOVL means moving by line
    enum TYPE{MOVJ=0, MOVL};
    // Coordinate type
    enum CoordType{CART=0, PULSE};

//    Move(Pose p, TYPE moveType, CoordType coordType)
//    {
//        this->p = p;
//        this->moveType = moveType;
//        this->coordType = coordType;
//    }


    // Pulse coordinate
//    double pulses[6];

    // Cartisian coordinate
    Pose p;

    TYPE moveType;
    CoordType coordType;
    double speed;
};



//w is the width of the string, e.g w=3 so 1->'001'
inline std::string int2str(int i, uint w=1)
{
    std::stringstream ioss;  //string stream
    std::string stmp;        //restore
    ioss<<i;
    ioss>>stmp;
    while(stmp.size()<w)
        stmp = '0' + stmp;
    return stmp;
}

// Find the nearest number to b in a, return the index of the nearest number.
inline int nearest(std::vector<float> a, float b)
{
    if(a.size() <=0 )
        return -1;

    int index = 0;
    float dmin = abs(a.at(0) - b);
    for(int i=1; i<a.size(); i++)
    {
        if( abs(a.at(i)-b)< dmin )
        {
            dmin = abs(a.at(i)-b);
            index = i;
        }
    }

    return index;
}

class Force6D
{
public:
    Force6D(double fx, double fy, double fz, double tx, double ty, double tz)
    {
        this->fx = fx;
        this->fy = fy;
        this->fz = fz;
        this->tx = tx;
        this->ty = ty;
        this->tz = tz;
    }
    Force6D(){}
    double fx,fy,fz;
    double tx,ty,tz;

};

class CurrenPoseWrite
{
public:
    CurrenPoseWrite(float x, float y, float z, float rx, float ry, float rz)
    {
        this->current_x = x;
        this->current_y = y;
        this->current_z = z;
        this->current_rx = rx;
        this->current_ry = ry;
        this->current_rz = rz;
    }
    CurrenPoseWrite(){}
    float current_x,current_y,current_z,current_rx,current_ry,current_rz;
};


#endif // COMMON_H
