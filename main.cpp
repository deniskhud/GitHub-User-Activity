#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h> 

using namespace std;

//contest -> ��������� �� ������; size, nmemb -> ������; output -> ������ ���� ����������
size_t WriteCallBack(void* contest, size_t size, size_t nmemb, string* output) {
	size_t totalSize = size * nmemb;
	output->append((char*)contest, totalSize);
	return totalSize;
}

void fetchGitHubActivity(const string& username) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    // ������������� CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // ������������� URL ��� �������
        string url = "https://api.github.com/users/" + username + "/events";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());   

        // ������������� ��������� ��� ������� (�������� ��������, ����� �������� ����������)
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "User-Agent: curl");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // ������������� ������� ��������� ������
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // ��������� ������
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "������ ��� �������: " << curl_easy_strerror(res) << endl;
        }
        else {
            // ������ ���������� ������ JSON
            Json::CharReaderBuilder readerBuilder;
            Json::Value jsonData;
            string errs;
            istringstream s(readBuffer);

            if (Json::parseFromStream(readerBuilder, s, &jsonData, &errs)) {
                for (const auto& event : jsonData) {
                    string type = event["type"].asString();
                    if (type == "PushEvent") {
                        string repo = event["repo"]["name"].asString();
                        int commits = event["payload"]["commits"].size();
                        cout << "- Pushed " << commits << " commits to " << repo << endl;
                    }
                    else if (type == "IssuesEvent" && event["payload"]["action"].asString() == "opened") {
                        string repo = event["repo"]["name"].asString();
                        cout << "- Opened a new issue in " << repo << endl;
                    }
                    else if (type == "WatchEvent") {
                        string repo = event["repo"]["name"].asString();
                        cout << "- Starred " << repo << endl;
                    }
                }
            }
            else {
                cerr << "������ ��� �������� JSON: " << errs << endl;
            }
        }

        // ����������� �������
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
}


int main() {
	
    string username;

    // ������ ��� ������������
    cout << "Enter GitHub username: ";
    cin >> username;

    // �������� ���������� ������������
    fetchGitHubActivity(username);
	

	return 0;
}