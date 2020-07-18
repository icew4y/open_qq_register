/*
 * EdUrlParser.h
 *
 *  Created on: Nov 25, 2014
 *      Author: netmind
 */

#ifndef EDURLPARSER_H_
#define EDURLPARSER_H_

#include <unordered_map>
#include <tuple>
#include <vector>
#include <string>

using namespace std;

typedef struct {
	string key;
	string val;
} query_kv_t;

typedef int (*__kv_callback)(void* list, string k, string v);

class EdUrlParser {
private:
	EdUrlParser();
public:
	virtual ~EdUrlParser();
	static EdUrlParser* parseUrl(string urlstr);
	static int parsePath(vector<string> *pdirlist, string pathstr);
	static string urlDecode(string str);
	static char toChar(const char* hex);
	static string urlEncode(string s);
	static void toHex(char *desthex, char c);
	static size_t parseKeyValueMap(unordered_map<string, string> *kvmap, string str, bool strict=true);
	static size_t parseKeyValueList(vector< query_kv_t > *kvmap, string rawstr, bool strict=true);
	static size_t parseKeyValue(string rawstr, __kv_callback kvcb, void* obj, bool strict);

private:
	void parse();

	string mRawUrl;
public:
	string scheme;
	string hostName;
	string port;
	string path;
	string query;
	string fragment;
};

#endif /* EDURLPARSER_H_ */

/*

int main() {
	string s =
			"http://www.google.co.kr:8080/testurl/depth1/depth2/depth3?name=james&id=100";

	// parse and allocate url object.
	EdUrlParser* url = EdUrlParser::parseUrl(s);
	cout << "scheme: " + url->scheme << endl;
	cout << "host name: " + url->hostName << endl;
	cout << "port: " + url->port << endl;
	cout << "path: " + url->path << endl;
	cout << "param: " + url->query << endl;
	cout << "fragment: " + url->fragment << endl;

	// parse path
	vector<string> paths;
	EdUrlParser::parsePath(&paths, url->path);
	for (int i = 0; i < paths.size(); i++) {
		cout << "path part: " + paths[i] << endl;
	}

	// parse query string as key-value list style
	vector<query_kv_t> kvs;
	int num = EdUrlParser::parseKeyValueList(&kvs, url->query);
	for(int i=0;i<num;i++) {
		printf("idx:%d  key: %s, val: %s\n", i, kvs[i].key.c_str(), kvs[i].val.c_str());
	}

	// parse query string as key-value hash map
	unordered_map<string, string> map;
	int mapnum = EdUrlParser::parseKeyValueMap(&map, url->query);
	string name;
	try {
		name = map.at("name");
		printf("key name vale '%s'\n", map["name"].c_str());
	} catch(out_of_range err) {
		printf("### Error: not found...\n");
	};


	if (url != NULL) // ==> make sure to free url object allocated by EdUrlParser
		delete url;

	// test url encoding
	string enc = EdUrlParser::urlEncode("left| |right & ");
	cout << "encoded string: " << enc << endl;
	string dec = EdUrlParser::urlDecode(enc);
	cout << "decoded string: " << dec << endl;

	return 0;
}

*/