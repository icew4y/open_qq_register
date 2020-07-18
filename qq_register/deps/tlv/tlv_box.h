/*
 *  COPYRIGHT NOTICE  
 *  Copyright (C) 2015, Jhuster, All Rights Reserved
 *  Author: Jhuster(lujun.hust@gmail.com)
 *  
 *  https://github.com/Jhuster/TLV
 *   
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.  
 */

#ifndef _TLV_BOX_H_
#define _TLV_BOX_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace tlv
{
    class Tlv;

    class TlvBox
    {
    public:
        TlvBox();
        virtual ~TlvBox();

    private:
        TlvBox(const TlvBox& c);
        TlvBox& operator=(const TlvBox& c);

    public:
        //put one TLV object
        bool PutBoolValue(short int type, bool value);
        bool PutCharValue(short int type, char value);
        bool PutShortValue(short int type, short value);
        bool PutIntValue(short int type, int value);
        bool PutLongValue(short int type, long value);
        bool PutLongLongValue(short int type, long long value);
        bool PutFloatValue(short int type, float value);
        bool PutDoubleValue(short int type, double value);
        bool PutStringValue(short int type, char* value);
        bool PutStringValue(short int type, const string& value);
        bool PutBytesValue(short int type, unsigned char* value, short int length);
        bool PutObjectValue(short int type, const TlvBox& value);

        //do encode
        bool Serialize();

        WORD GetTlvBoxCnt();
        //access encoded buffer and length
        unsigned char* GetSerializedBuffer() const;
        int GetSerializedBytes() const;

    public:
        //do decode
        bool Parse(const unsigned char* buffer, int buffersize);

        //get one TLV object
        bool GetBoolValue(short int type, bool& value) const;
        bool GetCharValue(short int type, char& value) const;
        bool GetShortValue(short int type, short& value) const;
        bool GetIntValue(short int type, int& value) const;
        bool GetLongValue(short int type, long& value) const;
        bool GetLongLongValue(short int type, long long& value) const;
        bool GetFloatValue(short int type, float& value) const;
        bool GetDoubleValue(short int type, double& value) const;
        bool GetStringValue(short int type, char* value, int& length) const;
        bool GetStringValue(short int type, string& value) const;
        // bool GetBytesValue(short int type,unsigned char *value, int &length) const;
        void GetBytesValue(short int type, vector<Tlv *>&) const;
        bool GetBytesValuePtr(short int type, unsigned char** value, int& length) const;
        bool GetObjectValue(short int type, TlvBox& value) const;

        vector<pair<short int, Tlv*>> GetAll() { return boxes; }

    private:
        bool PutValue(Tlv* value);

    private:

		vector<pair<short int, Tlv *>> boxes;

        map<short int, Tlv*> mTlvMap;
        unsigned char* mSerializedBuffer;
        int mSerializedBytes;
    };
} //namespace 

#endif //_TLVOBJECT_H_
