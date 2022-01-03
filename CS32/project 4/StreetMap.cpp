#include "provided.h"
#include <string>
#include <vector>
#include <functional>
#include "ExpandableHashMap.h"
#include <cctype>
#include <fstream>
#include <sstream>
using namespace std;

unsigned int hasher(const GeoCoord& g)
{
    return std::hash<std::string>()(g.latitudeText + g.longitudeText);
}

class StreetMapImpl
{
public:
    StreetMapImpl();
    ~StreetMapImpl();
    bool load(string mapFile);
    bool getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const;
private:
    ExpandableHashMap<GeoCoord, vector<StreetSegment>> m_hash;
};
    
StreetMapImpl::StreetMapImpl()
{
}

StreetMapImpl::~StreetMapImpl()
{
}

bool StreetMapImpl::load(string mapFile)
{
    ifstream inf(mapFile);
      // Test for failure to open
    if (!inf)
    {
        cerr << "Cannot open file" << endl;
        return false;
    }
    string s;
    string name;
    int i = 0;
    int length = 0;
    while(getline(inf,s)){
        istringstream iss(s);
        if(i ==0){
            name = s;
        }else if(i==1){
            iss >> length;
        }else{
            string lat1,lat2,long1,long2;
            iss >> lat1 >> long1 >> lat2 >> long2;
            GeoCoord g(lat1,long1);
            GeoCoord g2(lat2,long2);
//            cerr << g.latitudeText << " " << g.longitudeText << " " << g2.latitudeText << " " << g2.longitudeText << endl;
            const vector<StreetSegment>* pointer = m_hash.find(g);
            vector<StreetSegment> newone;
            newone.push_back(StreetSegment(g, g2, name));
            if(pointer == nullptr){
                m_hash.associate(g, newone);
            }
            else{
                for (vector<StreetSegment>::const_iterator it = pointer->begin(); it != pointer->end(); it++)
                {
                    newone.push_back(*it);
                }
                m_hash.associate(g, newone);
            }
            //reverse one
            pointer = m_hash.find(g2);
            newone.clear();
            newone.push_back(StreetSegment(g2, g, name));
            if(pointer == nullptr){
                m_hash.associate(g2, newone);
            }
            else{
                for (vector<StreetSegment>::const_iterator it = pointer->begin(); it != pointer->end(); it++)
                {
                    newone.push_back(*it);
                }
                m_hash.associate(g, newone);
            }
            if(i == length + 1){
                i = -1;
            }
        }
        i++;
    }
    return true;
}

bool StreetMapImpl::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
    const vector<StreetSegment>* pointer = m_hash.find(gc);
    if(pointer == nullptr){
        return false;
    }
    //if it is found then
    segs.clear();
    
    segs = *pointer;
    return true;
}

//******************** StreetMap functions ************************************

// These functions simply delegate to StreetMapImpl's functions.
// You probably don't want to change any of this code.

StreetMap::StreetMap()
{
    m_impl = new StreetMapImpl;
}

StreetMap::~StreetMap()
{
    delete m_impl;
}

bool StreetMap::load(string mapFile)
{
    return m_impl->load(mapFile);
}

bool StreetMap::getSegmentsThatStartWith(const GeoCoord& gc, vector<StreetSegment>& segs) const
{
   return m_impl->getSegmentsThatStartWith(gc, segs);
}
