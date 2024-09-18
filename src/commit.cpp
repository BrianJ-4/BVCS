#include <chrono>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string generateCommitID(const string& message)
{
    // Get the current system date and time
    const auto now = chrono::system_clock::now();
    const time_t t_c = chrono::system_clock::to_time_t(now);
    string time = ctime(&t_c);
    
    string combined = message + time;
    combined.erase(remove(combined.begin(), combined.end(), ' '), combined.end()); 
    
    hash<string> hasher;
    size_t hash = hasher(combined);
    return std::to_string(hash);
}

void commit(const vector<string>& messageVector)
{
    // Get the commit message
    string message;
    for (const auto& word : messageVector)
        message.append(word + " ");
    
    string commitID = generateCommitID(message);
    cout << commitID << endl;
}