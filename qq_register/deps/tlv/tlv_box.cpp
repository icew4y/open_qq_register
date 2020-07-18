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

#include <string.h>
#include "tlv.h"
#include "tlv_box.h"
#define htonl(u) ((((u) & 0xFF000000) >> 24) | (((u) & 0x00FF0000) >> 8) | (((u) & 0x0000FF00) << 8) | (((u) & 0x000000FF) << 24))
#define htons(n) ((((n) & 0xFF00) >> 8) | (((n) & 0x00FF) << 8))
#define ntohs(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

namespace tlv
{
    TlvBox::TlvBox() : mSerializedBuffer(nullptr), mSerializedBytes(0)
    {
    }

    TlvBox::~TlvBox()
    {
		if (mSerializedBuffer != nullptr)
		{
			delete[] mSerializedBuffer;
			mSerializedBuffer = nullptr;
		}

		map<short int, Tlv*>::iterator itor;
		for (itor = mTlvMap.begin(); itor != mTlvMap.end(); ++itor)
		{
			delete itor->second;
		}

		vector<pair<short int, Tlv *>>::iterator it;
		for (it = boxes.begin(); it != boxes.end(); ++it)
		{
			delete it->second;
		}
		mTlvMap.clear();
		boxes.clear();
		boxes.shrink_to_fit();
    }

    bool TlvBox::Serialize()
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }

        int offset = 0;
        mSerializedBuffer = new unsigned char[mSerializedBytes * 2];

        map<short, Tlv*>::iterator itor;

        size_t a = boxes.size();


        int i;
        for (i = 0; i < boxes.size(); i++)
        {
            //void *sec = boxes[i].second;
            short int type = ((Tlv *)boxes[i].second)->GetType();
            memcpy(mSerializedBuffer + offset, &type, sizeof(short int));
            offset += sizeof(short int);


            //length要网络字节序
            short int length = htons(((Tlv *)boxes[i].second)->GetLength());

            //short int length = ((Tlv *)boxes[i].second)->GetLength();
            memcpy(mSerializedBuffer + offset, &length, sizeof(short int));

            length = ntohs(length);
            offset += sizeof(short int);
            memcpy(mSerializedBuffer + offset, ((Tlv *)boxes[i].second)->GetValue(), length);
            offset += length;
        }

        //     for(itor=mTlvMap.begin();itor!=mTlvMap.end();itor++) {    
        //         int type = itor->second->GetType();
        //         memcpy(mSerializedBuffer+offset,&type,sizeof(short int));
        //         offset += sizeof(short int);
        // 
        // 		//length要网络字节序
        // 		short int length = htons(itor->second->GetLength());
        //         memcpy(mSerializedBuffer+offset,&length,sizeof(short int));
        // 		length = ntohs(length);
        //         offset += sizeof(short int);
        //         memcpy(mSerializedBuffer+offset,itor->second->GetValue(),length);        
        //         offset += length;
        //     }

        return true;
    }


    WORD TlvBox::GetTlvBoxCnt()
    {
        WORD result = 0;
        if (mSerializedBuffer == nullptr)
        {
            return 0;
        }

        // 	std::map<short, Tlv*>::iterator itor;
        // 	for (itor = mTlvMap.begin();itor != mTlvMap.end();itor++) 
        // 	{
        // 		result++;
        // 	}

        int i = 0;
        for (i = 0; i < boxes.size(); i ++)
        {
            result++;
        }

        return result;
    }

    bool TlvBox::Parse(const unsigned char* buffer, int buffersize)
    {
        //buffer += 2;//跳过TLV数量
        //buffersize -= 2;
        if (mSerializedBuffer != nullptr || buffer == nullptr)
        {
            return false;
        }

        unsigned char* cached = new unsigned char[buffersize];
        memcpy(cached, buffer, buffersize);

        int offset = 0;
        while (offset < buffersize)
        {
            short int type = ntohs((*(short int *)(cached+offset)));
            offset += sizeof(short int);
            short int length = ntohs((*(short int *)(cached+offset)));
            offset += sizeof(short int);
            PutValue(new Tlv(type, cached + offset, length));
            offset += length;
        }

        mSerializedBuffer = cached;
        mSerializedBytes = buffersize;

        return true;
    }

    unsigned char* TlvBox::GetSerializedBuffer() const
    {
        return mSerializedBuffer;
    }

    int TlvBox::GetSerializedBytes() const
    {
        return mSerializedBytes;
    }

    bool TlvBox::PutValue(Tlv* value)
    {
        //     std::map<short int,Tlv*>::const_iterator itor = mTlvMap.find(value->GetType());
        //     if (itor != mTlvMap.end()) 
        // 	{
        //         delete itor->second;        
        //     } else 
        // 	{
        //         mSerializedBytes += (sizeof(short int)*2+value->GetLength());
        //     }   
        // 
        // 	mTlvMap.insert(std::pair<short int,Tlv*>(value->GetType(),value));


        mSerializedBytes += (sizeof(short int) * 2 + value->GetLength());
		std::pair<short int, Tlv*> mpair = std::make_pair(value->GetType(), value);

        boxes.push_back(mpair);

        return true;
    }

    bool TlvBox::PutBoolValue(short int type, bool value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }

        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutCharValue(short int type, char value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutShortValue(short int type, short value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutIntValue(short int type, int value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutLongValue(short int type, long value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutLongLongValue(short int type, long long value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutFloatValue(short int type, float value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutDoubleValue(short int type, double value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutStringValue(short int type, char* value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutStringValue(short int type, const string& value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value));
    }

    bool TlvBox::PutBytesValue(short int type, unsigned char* value, short int length)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, value, length));
    }

    bool TlvBox::PutObjectValue(short int type, const TlvBox& value)
    {
        if (mSerializedBuffer != nullptr)
        {
            return false;
        }
        unsigned char* buffer = value.GetSerializedBuffer();
        if (buffer == nullptr)
        {
            return false;
        }
        return PutValue(new Tlv(type, buffer, value.GetSerializedBytes()));
    }

    bool TlvBox::GetBoolValue(short int type, bool& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(bool *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetCharValue(short int type, char& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(char *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetShortValue(short int type, short& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(short *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetIntValue(short int type, int& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(int *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetLongValue(short int type, long& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(long *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetLongLongValue(short int type, long long& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(long long *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetFloatValue(short int type, float& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(float *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetDoubleValue(short int type, double& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (*(double *)(itor->second->GetValue()));
            return true;
        }
        return false;
    }

    bool TlvBox::GetStringValue(short int type, char* value, int& length) const
    {
        //return GetBytesValue(type,(unsigned char *)value,length);
        return false;
    }

    bool TlvBox::GetStringValue(short int type, string& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor != mTlvMap.end())
        {
            value = (char *)(itor->second->GetValue());
            return true;
        }
        return false;
    }

    void TlvBox::GetBytesValue(short int type, vector<Tlv *>& vectors) const
    {
        //     std::map<short int,Tlv*>::const_iterator itor = mTlvMap.find(type);
        //     if (itor == mTlvMap.end()) {
        //         return false;
        //     }
        // 
        //     if (length < itor->second->GetLength()) {
        //         return false;
        //     }
        // 
        //     memset(value,0,length);
        //     length = itor->second->GetLength();
        //     memcpy(value,itor->second->GetValue(),length);

        size_t a = boxes.size();


        int i;
        for (i = 0; i < boxes.size(); i++)
        {
            if (type == boxes[i].first)
            {
                vectors.push_back((Tlv*)boxes[i].second);
            }
        }
    }

    bool TlvBox::GetBytesValuePtr(short int type, unsigned char** value, int& length) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor == mTlvMap.end())
        {
            return false;
        }
        *value = itor->second->GetValue();
        length = itor->second->GetLength();
        return true;
    }

    bool TlvBox::GetObjectValue(short int type, TlvBox& value) const
    {
        map<short int, Tlv*>::const_iterator itor = mTlvMap.find(type);
        if (itor == mTlvMap.end())
        {
            return false;
        }
        return value.Parse(itor->second->GetValue(), itor->second->GetLength());
    }
} //namespace 
