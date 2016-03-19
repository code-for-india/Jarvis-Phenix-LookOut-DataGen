#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <cstdio>
#include <set>
#include <map>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <cassert>
#include <sstream>
#include <ctime>
#include <fstream>

using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef stringstream SS;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(a) MAX(a,-(a))

#define SS(a) scanf("%d",&a)
#define SZ(a) ((int)a.size())
#define PB(a) push_back(a)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define REP(i,n) FOR(i,0,(int)(n-1))
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define printv(v) REP(i,SZ(v))printf("%d ",v[i]);
#define mp(a,b) make_pair(a,b)
#define MOD 1000000007
#define INF 2147483647
#define MS_SEC 1000

enum loo_field{
  LOO_BEGIN,
  ID,
  ADDRESS,
  LATITUDE,
  LONGITUDE,
  TIMING,
  TYPE,
  URINAL_COUNT,
  HANDICAP,
  PAID,
  AVG_RATING,
  PICTURE_URL,
  CREATED_AT,
  UPDATED_AT,
  LOO_END
};

#define INTEGER 0
#define STRING 1

string strloo_fields = "id,address,latitude,longitude,timing,type,urinal_count,handicap_support,paid,avg_rating,picture_url,created_at,updated_at";
int loos_datatype[] = {INTEGER, STRING, INTEGER, INTEGER, STRING, STRING, INTEGER, INTEGER, INTEGER, INTEGER, STRING, INTEGER, INTEGER};
vector <string> loo_fields;

string strvisits_fields = "id, loo_id, created_at, updated_at";
int visits_datatype[] = {INTEGER, INTEGER, INTEGER, INTEGER};
vector <string> visits_fields;

string strissue_fields = "id, user_id, loo_id, issue_type, comment, picture_url, state, source, gender, resolved_at, created_at, updated_at";
vector <string> issues_fields;
int issues_datatype[] = {INTEGER, STRING, INTEGER, STRING, STRING, STRING, STRING, STRING, STRING, INTEGER, INTEGER, INTEGER};

string strsubdistricts = "Darya Ganj, Pahar Ganj, Karol Bagh,Sadar Bazar, Kotwali, Sabzi Mandi,Kalkaji, Defence Colony, Hauz Khas,Gandhi Nagar, Preet Vihar, Vivek Vihar, Vasundhara Enclave,Seelampur, Snehahdara, Seema Puri,Vasant Vihar, Najafgarh, Delhi Cantt,Connaught Place, Parliament Street, Chanakya Puri,Saraswati Vihar, Narela, Model Town,Patel Nagar, Rajouri Garden, Punjabi Bagh";
vector <string> subdistricts;

string strtimings = "0700-1800,1200-2400,0500-1900,1000-2200";
vector <string> timings;

string toiletType = "Indian, Western, Indian/Western";
vector <string> toiletTypes;

const double MIN_LATITUDE = 28.481216;
const double MAX_LATITUDE = 28.67;

const double MIN_LONGITUDE = 77.019135;
const double MAX_LONGITUDE = 77.42;

const int MIN_URINALS = 1;
const int MAX_URINALS = 7;

const int HANDICAP_NO = 0;
const int HANDICAP_YES = 1;

const int PAID_NO = 0;
const int PAID_YES = 1;

const double MIN_RATING = 1;
const double MAX_RATING = 5;

const ULL CREATED_START = 1452599523000;
const ULL UPDATED_START = 1452599523000;

vector<string> splitOnComma(string input)
{
  string str;
  vector <string> out;
  for (int i=0;i<input.size();i++) {
    if(input[i] == ',') {
      out.push_back(str);
      str = "";
    }
    else
    {
      if(!str.size() && input[i] == ' ');
      else str = str + input[i];
    }
  }
  out.push_back(str);
  return out;
}

void initialize_loos()
{
  loo_fields = splitOnComma(strloo_fields);
  subdistricts = splitOnComma(strsubdistricts);
//  for (int i=0;i<subdistricts.size();i++) {
//    cout << subdistricts[i] << endl;
//  }
  timings = splitOnComma(strtimings);
  toiletTypes = splitOnComma(toiletType);
}

void initialize_visits()
{
  visits_fields = splitOnComma(strvisits_fields);
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int iRand(int iMin, int iMax)
{
  return iMin + (rand() % (iMax - iMin + 1));
}

LL lRand(LL iMin, LL iMax) {
  LL range = iMax - iMin + 1;
  LL tsRand = (( ((LL)rand()) << 48 ) | ( ((LL)rand()) << 32 ) | ( ((LL)rand()) << 16 ) | ( ((LL)rand()) )) % range;
  return iMin + (tsRand % (range));
}

int iRandWeight(int iMin, int iMax, vector <int> w = vector <int>())
{
  vector <int> weights(iMax - iMin + 1);
  LL sum = 0;
  if (!w.size()) {
    for (int i=0;i<weights.size();i++) {
      weights[i] = (rand() % 10) + 1;
      sum += weights[i];
    }
  } else {
    for (int i=0;i<w.size();i++) {
      weights[i] = w[i];
    }
  }
  LL randWeight = rand() % sum;
  LL localSum = 0;
  for (int i=iMin; i <= iMax;i++) {
    if(localSum >= randWeight) {
      return i;
    }
    cout << i - iMin << weights[i-iMin] << endl;
    localSum += weights[i-iMin];
  }
  return iMin + (rand() % (iMax - iMin + 1));
}


string loo_randomFields(loo_field field, string str = "")
{
  stringstream ss;
  switch(field){
  case LOO_BEGIN:
    break;
  case ID:
    return str;
  case ADDRESS:
    return subdistricts[rand() % subdistricts.size()];
  case LATITUDE:
    ss << fRand(MIN_LATITUDE,MAX_LATITUDE);
    break;
  case LONGITUDE:
    ss << fRand(MIN_LONGITUDE, MAX_LONGITUDE);
    break;
  case TIMING:
    return timings[rand() % timings.size()];
  case TYPE:
    return toiletTypes[rand() % toiletTypes.size()];
  case URINAL_COUNT:
    ss << iRand(MIN_URINALS, MAX_URINALS);
    break;
  case HANDICAP:
    ss << iRand(HANDICAP_NO, HANDICAP_YES);
    break;
  case PAID:
    ss << iRandWeight(PAID_NO, PAID_YES);
    break;
  case AVG_RATING:
    ss << fRand(MIN_RATING, MAX_RATING);
    break;
  case PICTURE_URL:
    return "";
  case CREATED_AT:
    {
      ULL ts = CREATED_START;
      int days = 90;
      ULL range = ((ULL)days * 86400) * MS_SEC;
      ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
      ss << ts + tsrand;
    }
    break;
  case UPDATED_AT:
    {
      ULL ts = CREATED_START;
      int days = 90;
      ULL range = ((ULL)days * 86400) * MS_SEC;
      ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
      ss << ts + tsrand;
    }
  }
  return ss.str();
}

enum visit_field{
  VBEGIN,
  V_ID,
  F_LOO_ID,
  V_CREATED_AT,
  V_UPDATED_AT,
  VEND
};

string visits_randomFields(visit_field field, string str = "")
{
  stringstream ss;
  switch(field){
  case VBEGIN:
    break;
  case V_ID:
    return str;
  case F_LOO_ID:
    ss << iRandWeight(0,99);
    break;
  case V_CREATED_AT:
    {
      ULL ts = CREATED_START;
      int days = 90;
      ULL range = ((ULL)days * 86400) * MS_SEC;
      ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
      ss << ts + tsrand;
    }
    break;
  case V_UPDATED_AT:
    {
      ULL ts = CREATED_START;
      int days = 90;
      ULL range = ((ULL)days * 86400) * MS_SEC;
      ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
      ss << ts + tsrand;
    }
  }
  return ss.str();
}

string strIssueType = "dirty,no soap,no water,broken";
vector <string> issueTypes;
int issueTypeWeight[] = {9, 4, 6, 2};

string strState = "pending, resolved";
vector <string> states;

string strSource = "app, hardware";
vector <string> sources;

string strGender = "male, female";
vector <string> gender;
int genderWeight[] = {9,4};

enum issue_fields{
 I_BEGIN,
 I_ID,
 USERID,
 I_LOO_ID,
 ISSUE_TYPE,
 COMMENT,
 I_PICTURE_URL,
 STATE,
 SOURCE,
 GENDER,
 RESOLVED_AT,
 I_CREATED_AT,
 I_UPDATED_AT,
 I_END
};

const int MIN_USERID = 1;
const int MAX_USERID = 10000;

const int MIN_LOOID = 0;
const int MAX_LOOID = 99;

void initialize_issues()
{
  issueTypes = splitOnComma(strIssueType);
  states = splitOnComma(strState);
  sources = splitOnComma(strSource);
  gender = splitOnComma(strGender);
  issues_fields = splitOnComma(strissue_fields);
}

string issues_randomFields(issue_fields field, string str = "", ULL startDate = 0, int dayInterval = 0) {
  stringstream ss;
  switch(field){
  case I_BEGIN:
    break;
  case I_ID:
    return str;
  case USERID:
    ss << (char) ('A' + rand() % 26) << iRand(MIN_USERID, MAX_USERID);
    break;
  case I_LOO_ID:
    ss << iRandWeight(MIN_LOOID, MAX_LOOID);
    break;
  case ISSUE_TYPE:
    {
    vector <int> w(issueTypes.size());
    for (int i=0;i<w.size();i++) w[i] = issueTypeWeight[i];
    return issueTypes[iRandWeight(0, issueTypes.size() - 1, w)];
    }
  case STATE:
    return states[rand() % states.size()];
  case SOURCE:
    return sources[rand() % sources.size()];
  case GENDER:
    {
    vector <int> w (gender.size());
    for (int i=0;i<gender.size();i++) w[i] = genderWeight[i];
    return gender[iRandWeight(0, gender.size() - 1, w) % gender.size()];
    }
  case RESOLVED_AT:
  case I_CREATED_AT:
  case I_UPDATED_AT:
    {
      if(!startDate) {
      ULL ts = CREATED_START;
      int days = 90;
      ULL range = ((ULL)days * 86400) * MS_SEC;
      ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
      ss << ts + tsrand;
      } else {
        ULL ts = startDate;
        int dayWeights[] = {5,5,5,5,5,5,5,5,5,9};
        vector <int> w(10);
        int days = 10;
        for (int i=0;i<w.size();i++) w[i] = dayWeights[i];
        int index = iRandWeight(0, 10, w);
        if(index == 9)
          days = 30;
        else days = index + 1;
        ULL range = ((ULL)days * 86400) * MS_SEC;
        ULL tsrand = (( ((ULL)rand()) << 48 ) | ( ((ULL)rand()) << 32 ) | ( ((ULL)rand()) << 16 ) | ( ((ULL)rand()) )) % range;
        ss << ts + tsrand;
      }
    }
    break;
  case COMMENT:
    break;
  case I_PICTURE_URL:
    break;
  case I_END:
  default:;
  }
  return ss.str();
}

void generate_csv(int n, string fileName, vector <string> data[])
{
  ofstream fout(fileName.c_str());
  // CSV
  for (int i=0;i<n;i++) {
    for (int j=0;j<data[i].size();j++) {
      fout << data[i][j];
      if ( j != data[i].size() - 1)
        fout << ",";
    }
    fout << endl;
  }
  fout.close();
}

void generate_json(int n, string fileName, vector <string> data_fields, vector <string> data[])
{
  ofstream fout(fileName.c_str());
  for (int i=0;i<n;i++) {
    fout << "{";
    for (int j=0;j < data[i].size(); j++) {
      fout << "\"" << data_fields[j] << "\":\"" << data[i][j] << "\"";
      if ( j != data[i].size() - 1)
        fout << ",";
    }
    fout << "}" << endl;
  }
  fout.close();
}

string toQuoteOrNot(string s, int flag) {
  if (flag)
    return "'" + s + "'";
  return s;
}

void generate_sql(int n, string fileName, string tableName, vector <string> data_fields, int data_type[], vector <string> data[])
{
  ofstream fout(fileName.c_str());
  fout << "INSERT INTO " << tableName << "(";

  for (int i=0;i<data_fields.size();i++) {
    fout << data_fields[i];
    if (i != data_fields.size() - 1)
      fout << ',';
  }
  fout << ')';
  fout << "\nVALUES ";
  for (int i=0;i < n; i++) {
    fout << '(';
    for (int j=0;j < data[i].size();j++) {
      fout << toQuoteOrNot(data[i][j], data_type[j]);
      if (j != data[i].size() - 1)
        fout << ",";
    }
    fout << ')';
    if (i != n-1)
      fout << ',';
    fout << endl;
  }
  fout.close();
}

string strattendance_fields = "id,sc_id,presence,time";
vector <string> attendance_fields;

void initialize_exam() {
  attendance_fields = splitOnComma(strattendance_fields);
}

string toString(LL n) {
  stringstream ss;
  ss << n;
  return ss.str();
}

void examination() {
  srand(time(NULL));
  initialize_exam();
  int n;
  cin >> n;

  int iid = 1;
  vector <string> studCourses[1000];
  for (int i=1; i <= n; i++) {
    int k = iRand(3, 6);
    string row;
    for (int j=1; j <= k; j++) {
      studCourses[iid-1].push_back(toString(iid));
      studCourses[iid-1].push_back(toString(i));
      studCourses[iid-1].push_back(toString(j));
      iid++;
    }
  }
  string strrand = "student_courses";
  generate_csv(iid, strrand + ".csv", studCourses);

  vector <string> attendance[100000];
  LL startTime = 1420070400000;
  LL endTime = startTime + (86400 * MS_SEC);

  vector <LL> thresholds;
  LL month = 2592000000LL;
  LL check = startTime;
  for (int i=0;check < startTime + (((LL)365 * 86400) * MS_SEC);i++) {
    check = check + month;
    thresholds.push_back(check);
    cout << check << endl;
  }
  int thresCount = 0;
  int a[] = {8,8,6,8,9,9,9,7,7,8,8,5,7};

  int iCnt = 0;
  for (int day=0; day < 365; day++ ) {
    for (int i=1;i < iid;i++) {
      attendance[iCnt].push_back(toString(iCnt+1));
      attendance[iCnt].push_back(toString(i));
      int k = rand() % 10;
      int presence = 1;
      if (k < a[thresCount]) presence = 1;
      else presence = 0;
      attendance[iCnt].push_back(toString(presence));
      LL tmStamp = lRand(startTime, endTime);
      attendance[iCnt].push_back(toString(tmStamp));
      iCnt++;
    }
    startTime += (((LL)86400) * MS_SEC);
    endTime += (((LL)86400) * MS_SEC);
    if (startTime > thresholds[thresCount]) {
      thresCount++;
    }
  }
  string attendanceFileName = "attendance";
  generate_csv(iCnt, attendanceFileName + ".csv", attendance);
}


int main(){
  srand(time(NULL));
  examination();
  return 0;
  /////////////////////////////////////////////////////////////
  srand(time(NULL));
  stringstream ss;
  ss << 40000 + rand() % 10000;

  string fileName = "loo" + ss.str();
  cout << fileName;
  //freopen(fileName.c_str(),"w",stdout);

  initialize_loos();
  int nLoos;
  cin >> nLoos;
  vector <string> looData[nLoos];
  for (int i = 0; i < nLoos; i++ ) {
    stringstream ss;
    ss << i;
    for (int j = LOO_BEGIN; j + 1 < LOO_END; j++) {
      if ((loo_field) (j + 1) == ID )
        looData[i].push_back(loo_randomFields((loo_field)(j+1), ss.str()));
      else
        looData[i].push_back(loo_randomFields((loo_field)(j+1)));
    }
  }
  generate_csv(nLoos, fileName + ".csv", looData);
  generate_json(nLoos, fileName + ".json", loo_fields, looData);
  generate_sql(nLoos, fileName + ".sql", "loos", loo_fields, loos_datatype, looData);
//  // CSV
//  for (int i=0;i<nLoos;i++) {
//    for (int j=0;j<looData[i].size();j++) {
//      cout << looData[i][j];
//      if ( j != looData[i].size() - 1)
//        cout << ",";
//    }
//    cout << endl;
//  }
//
//  cout << endl;
//  cout << "BEGIN JSON\n";
//  // JSON
//  for (int i=0;i<nLoos;i++) {
//    cout << "{";
//    for (int j=0;j<looData[i].size();j++) {
//      cout << "\"" << loo_fields[j] << "\":\"" << looData[i][j] << "\"";
//      if ( j != looData[i].size() - 1)
//        cout << ",";
//    }
//    cout << "}" << endl;
//  }
  initialize_visits();
  string visitsFileName = "visits" + ss.str();

  int visits;
  cin >> visits;

  vector <string> visitsData[visits];
  for (int i = 0; i < visits; i++ ) {
    stringstream ss;
    ss << i + 1;
    for (int j = VBEGIN; j + 1 < VEND; j++) {
      if ((visit_field) (j + 1) == V_ID )
        visitsData[i].push_back(visits_randomFields((visit_field)(j+1), ss.str()));
      else
        visitsData[i].push_back(visits_randomFields((visit_field)(j+1)));
    }
  }

  generate_csv(visits, visitsFileName + ".csv", visitsData);
  generate_json(visits, visitsFileName + ".json", visits_fields, visitsData);
  generate_sql(visits, visitsFileName + ".sql", "visits", visits_fields, visits_datatype, visitsData);

  initialize_issues();
  int issues;
  cin >> issues;
  string issuesFileName = "issues" + ss.str();
  vector <string> issueData[issues];
  for (int i = 0; i < issues; i++ ) {
    stringstream ss;
    ss << i + 1;
    for (int j = I_BEGIN; j + 1 < I_END; j++) {
      if ((issue_fields) (j + 1) == I_ID )
        issueData[i].push_back(issues_randomFields((issue_fields)(j+1), ss.str()));
      else
        issueData[i].push_back(issues_randomFields((issue_fields)(j+1)));
    }
  }
  // Resolved at null when state pending
  for (int i = 0; i < issues; i++) {
    if (issueData[i][6] == "pending")
      issueData[i][9] = "";
  }

  // Created at, resolved at should be within 10 days
  for (int i = 0;i < issues; i++) {
    ULL created_at, resolved_at = 0;
    stringstream ss;
    ss << issueData[i][10];
    ss >> created_at;
    stringstream ss2;
    ss2 << issueData[i][9];
    ss2 >> resolved_at;
    if (issueData[i][9] != "" && created_at > resolved_at)
    {
      stringstream ss;
      while (created_at > resolved_at)
      {
        ss << issues_randomFields(RESOLVED_AT, "", created_at, 10);
        ss >> resolved_at;
        ss.str("");
      }
      stringstream ss2;
      ss2 << resolved_at;
      ss2 >> issueData[i][9];
    }
  }

  generate_csv(issues, issuesFileName + ".csv", issueData);
  generate_json(issues, issuesFileName + ".json", issues_fields, issueData);
  generate_sql(issues, issuesFileName + ".sql", "issues", issues_fields, issues_datatype, issueData);
  return 0;
}

