#include "provided.h"
#include <list>
#include <queue>
#include "ExpandableHashMap.h"
#include <map>
#include <vector>
using namespace std;

class PointToPointRouterImpl
{
public:
    PointToPointRouterImpl(const StreetMap* sm);
    ~PointToPointRouterImpl();
    DeliveryResult generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const;
private:
    void bubbleSort(vector<StreetSegment>& seg) const;
    const StreetMap* m_strmap;
    bool isValid(GeoCoord g) const;
};

PointToPointRouterImpl::PointToPointRouterImpl(const StreetMap* sm)
{
    m_strmap = sm;
}

PointToPointRouterImpl::~PointToPointRouterImpl()
{
//    delete m_strmap;
}

bool PointToPointRouterImpl::isValid(GeoCoord g) const{
    vector<StreetSegment> seg;
    if(m_strmap->getSegmentsThatStartWith(g, seg)){
        return true;
    }
    cerr << g.latitudeText << " " << g.longitudeText << endl;
    return false;
}

void PointToPointRouterImpl::bubbleSort(vector<StreetSegment> &seg) const{
       int i, j;
       bool swapped;
       for (i = 0; i < seg.size()-1; i++)
       {
         swapped = false;
         for (j = 0; j < seg.size()-i-1; j++)
         {
            if(distanceEarthMiles(seg[j].start, seg[j].end) > distanceEarthMiles(seg[j+1].start, seg[j+1].end)){
                StreetSegment temp = seg[j];
                seg[j] = seg[j+1];
                seg[j+1] = temp;
            }
         }
         // IF no two elements were swapped by inner loop, then break
         if (swapped == false)
             return;
       }
}

DeliveryResult PointToPointRouterImpl::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    if(!isValid(start) || !isValid(end)){
        return BAD_COORD;
    }
    route.clear();
    totalDistanceTravelled = 0;
    //in case the starting point is ending point
    if(start == end){
        return DELIVERY_SUCCESS;
    }
    queue<GeoCoord> coord;
    map<GeoCoord, StreetSegment> prevLoc;
    coord.push(start);
    GeoCoord temp;
    bool found = false;
    while(!coord.empty()){
        temp = coord.front();
        coord.pop();
        if(temp==end){
            //update route and distance
            found =true;
            break;
        }
        vector<StreetSegment> seg;
        m_strmap->getSegmentsThatStartWith(temp, seg);
        //order seg with shortest distance min -> max
        bubbleSort(seg);
        
        //find path
        for(int i = 0; i < seg.size(); i++){
            if(prevLoc.find(seg[i].end) == prevLoc.end() && seg[i].end != start){
                coord.push(seg[i].end);
                prevLoc[seg[i].end] = seg[i];
//                cerr << seg[i].end.latitudeText << " " << seg[i].end.longitudeText << " "<< seg[i].start.latitudeText << " " << seg[i].start.longitudeText << endl;
            }
        }
    }
    if(found){
        cerr << "entering the while loop" <<endl;
        while(temp!=start){
            cerr << "TEMP is: " << temp.latitudeText << " " << temp.longitudeText << endl;
            StreetSegment previous = prevLoc[temp];
            cerr << "Street: " << previous.name << endl;
            totalDistanceTravelled+=distanceEarthMiles(previous.start, previous.end);
            route.push_back(previous);
            temp = previous.start;
        }
        cerr << "exited" << endl;
        //since the list was added destination to start, reverse the order
        route.reverse();
        return DELIVERY_SUCCESS;
    }
    return NO_ROUTE;
}

//******************** PointToPointRouter functions ***************************

// These functions simply delegate to PointToPointRouterImpl's functions.
// You probably don't want to change any of this code.

PointToPointRouter::PointToPointRouter(const StreetMap* sm)
{
    m_impl = new PointToPointRouterImpl(sm);
}

PointToPointRouter::~PointToPointRouter()
{
    delete m_impl;
}

DeliveryResult PointToPointRouter::generatePointToPointRoute(
        const GeoCoord& start,
        const GeoCoord& end,
        list<StreetSegment>& route,
        double& totalDistanceTravelled) const
{
    return m_impl->generatePointToPointRoute(start, end, route, totalDistanceTravelled);
}
