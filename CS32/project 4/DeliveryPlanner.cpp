#include "provided.h"
#include <vector>
#include <list>
using namespace std;

class DeliveryPlannerImpl
{
public:
    DeliveryPlannerImpl(const StreetMap* sm);
    ~DeliveryPlannerImpl();
    DeliveryResult generateDeliveryPlan(
        const GeoCoord& depot,
        const vector<DeliveryRequest>& deliveries,
        vector<DeliveryCommand>& commands,
        double& totalDistanceTravelled) const;
private:
    string direction(double angle) const;
    const StreetMap* m_strmap;
    void updating(list<StreetSegment> route, vector<DeliveryCommand>& commands) const;
};

DeliveryPlannerImpl::DeliveryPlannerImpl(const StreetMap* sm)
{
    m_strmap = sm;
}

DeliveryPlannerImpl::~DeliveryPlannerImpl()
{
}
string DeliveryPlannerImpl::direction(double angle) const{
    if(angle < 22.5){
        return "east";
    }
    else if(angle < 67.5){
        return "northeast";
    }
    else if(angle < 112.5){
        return "north";
    }
    else if(angle < 157.5){
        return "northwest";
    }
    else if(angle < 202.5){
        return "west";
    }
    else if(angle < 247.5){
        return "southwest";
    }
    else if(angle < 292.5){
        return "south";
    }
    else if(angle < 337.5){
        return "southeast";
    }
    else{
        return "east";
    }
}

void DeliveryPlannerImpl::updating(list<StreetSegment> route, vector<DeliveryCommand>& commands) const{
    list<StreetSegment>::iterator it;
    StreetSegment s;
    DeliveryCommand m;
    for(it = route.begin(); it != route.end(); it++){
        list<StreetSegment>::iterator it2;
        for(it2 = ++it; it2 != route.end(); it2++){
            if(it->name != it2->name){
                s = StreetSegment(it->start, it2->start, it->name);
                m.initAsProceedCommand(direction(angleOfLine(s)), s.name, distanceEarthMiles(s.start, s.end));
                commands.push_back(m);
                it = it2--;
                m.initAsTurnCommand(direction(angleBetween2Lines(*it, *it2)), it2->name);
                commands.push_back(m);
                break;
            }
        }
    }
}
DeliveryResult DeliveryPlannerImpl::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    //reorder them after doing the optimizer
    double oldCrowDist, newCrowDist;
    DeliveryOptimizer* var = new DeliveryOptimizer(m_strmap);
    vector<DeliveryRequest> newDeliveries = deliveries;
    var->optimizeDeliveryOrder(depot, newDeliveries, oldCrowDist, newCrowDist);
    list<StreetSegment> route;
    double dist;
    PointToPointRouter* router = new PointToPointRouter(m_strmap);
    GeoCoord start = depot;
    for(int i = 0; i < newDeliveries.size(); i++){
        if(router->generatePointToPointRoute(start, newDeliveries[i].location, route, dist) == BAD_COORD){
            return BAD_COORD;
        }
        if(router->generatePointToPointRoute(start, newDeliveries[i].location, route, dist) == NO_ROUTE){
            return NO_ROUTE;
        }
        updating(route, commands);
        DeliveryCommand m;
        m.initAsDeliverCommand(newDeliveries[i].item);
        commands.push_back(m);
        start = newDeliveries[i].location;
        totalDistanceTravelled+=dist;
    }
    //time to go back home
    router->generatePointToPointRoute(start, depot, route, dist);
    updating(route, commands);
    totalDistanceTravelled+=dist;
    return DELIVERY_SUCCESS;  // Delete this line and implement this function correctly
}

//******************** DeliveryPlanner functions ******************************

// These functions simply delegate to DeliveryPlannerImpl's functions.
// You probably don't want to change any of this code.

DeliveryPlanner::DeliveryPlanner(const StreetMap* sm)
{
    m_impl = new DeliveryPlannerImpl(sm);
}

DeliveryPlanner::~DeliveryPlanner()
{
    delete m_impl;
}

DeliveryResult DeliveryPlanner::generateDeliveryPlan(
    const GeoCoord& depot,
    const vector<DeliveryRequest>& deliveries,
    vector<DeliveryCommand>& commands,
    double& totalDistanceTravelled) const
{
    return m_impl->generateDeliveryPlan(depot, deliveries, commands, totalDistanceTravelled);
}
