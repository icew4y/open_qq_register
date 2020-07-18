#pragma once
#include "tlv_t.h"
#include "../protobuf_proto/DeviceReport.pb.h"

/*

 Tagindex: 1325(0x052D)  -> (android_dev_info(protobuf))
										Length: 361(0x0169)
										Value: 0A 0C 61 6E 67 6C 65 72 2D 30 31 2E 33 31 12 AC 01 4C 69 6E 75 78 20 76 65 72 73 69 6F 6E 20 33 2E 31 30 2E 37 33 2D 67 39 62 36 35 39 36 64 20 28 61 6E 64 72 6F 69 64 2D 62 75 69 6C 64 40 76 70 61 6B 34 2E 6D 74 76 2E 63 6F 72 70 2E 67 6F 6F 67 6C 65 2E 63 6F 6D 29 20 28 67 63 63 20 76 65 72 73 69 6F 6E 20 34 2E 39 2E 78 2D 67 6F 6F 67 6C 65 20 32 30 31 34 30 38 32 37 20 28 70 72 65 72 65 6C 65 61 73 65 29 20 28 47 43 43 29 20 29 20 23 31 20 53 4D 50 20 50 52 45 45 4D 50 54 20 53 61 74 20 53 65 70 20 32 36 20 31 38 3A 31 37 3A 35 39 20 55 54 43 20 32 30 31 35 1A 03 52 45 4C 22 07 32 32 39 34 38 31 39 2A 39 67 6F 6F 67 6C 65 2F 61 6E 67 6C 65 72 2F 61 6E 67 6C 65 72 3A 36 2E 30 2F 4D 44 41 38 39 44 2F 32 32 39 34 38 31 39 3A 75 73 65 72 2F 72 65 6C 65 61 73 65 2D 6B 65 79 73 32 24 35 64 37 37 30 63 34 31 2D 34 66 39 64 2D 34 65 33 30 2D 62 34 36 30 2D 30 63 34 37 62 63 30 32 38 37 30 34 3A 10 34 32 36 38 65 66 61 30 33 61 34 66 64 30 35 61 42 20 2E 32 2E 36 2E 31 2E 63 34 2D 30 30 30 30 34 2D 4D 38 39 39 34 46 41 41 41 41 4E 41 5A 4D 2D 31 4A 07 32 32 39 34 38 31 39


										
		this.bytes_bootloader = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_version = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_codename = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_incremental = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_fingerprint = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_boot_id = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_android_id = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_baseband = PBField.initBytes(ByteStringMicro.EMPTY);
		this.bytes_inner_ver = PBField.initBytes(ByteStringMicro.EMPTY);
										*/
class tlv_t52d : public tlv_t
{
public:
	tlv_t52d() {
		this->_cmd = 0x52d;
	}
	string get_tlv_t52d(string& android_id) {
		string buffer;
		DeviceReport devreport; {
			devreport.set_bytes_bootloader("angler-03.52");
			devreport.set_bytes_version("android-build@vpak5.mtv.corp.google.com) (gcc version 4.9.x-google 20140827 (prerelease) (GCC) ) #1 SMP PREEMPT Wed Jun 8 18:39:54 UTC 2016");
			devreport.set_bytes_codename("REL");
			devreport.set_bytes_incremental("2960136");
			devreport.set_bytes_fingerprint("google/angler/angler:6.0.1/MTC19X/2960136:user/release-keys");
			devreport.set_bytes_boot_id("0d35b728-4f3e-4cb9-b5e4-08c67b71ab04");
			devreport.set_bytes_android_id(android_id);
			devreport.set_bytes_baseband("angler-03.61");
			devreport.set_bytes_inner_ver("2960136");
		}

		devreport.SerializeToString(&buffer);

		this->fill_head();
		this->fill_body(buffer);
		return this->get_buf();
	}
protected:
private:

};