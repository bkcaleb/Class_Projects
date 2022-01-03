#include "provided.h"
#include <vector>
using namespace std;

class DeliveryOptimizerImpl
{
public:
    DeliveryOptimizerImpl(const StreetMap* sm);
    ~DeliveryOptimizerImpl();
    void optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const;
private:
    int calculatingDist(const GeoCoord& depot, vector<DeliveryRequest> deliveries) const;
    const StreetMap* m_strmap;
};

DeliveryOptimizerImpl::DeliveryOptimizerImpl(const StreetMap* sm)
{
    m_strmap = sm;
}

DeliveryOptimizerImpl::~DeliveryOptimizerImpl()
{
}

int DeliveryOptimizerImpl::calculatingDist(const GeoCoord& depot, vector<DeliveryRequest> deliveries) const{
    if(deliveries.empty()){
        return 0;
    }
    double distance = 0;
    for(int i = 0; i < deliveries.size()-1; i++){
        distance+=distanceEarthMiles(deliveries[i].location, deliveries[i+1].location);
    }
    //depot to first point and last point to depot
    distance+=distanceEarthMiles(depot, deliveries[0].location);
    distance+=distanceEarthMiles(deliveries[deliveries.size()-1].location, depot);
    return distance;
}
void DeliveryOptimizerImpl::optimizeDeliveryOrder(
    const GeoCoord& depot,
    vector<DeliveryRequest>& deliveries,
    double& oldCrowDistance,
    double& newCrowDistance) const
{
    oldCrowDistance = calculatingDist(depot, deliveries);
    //optimization
    GeoCoord comparing = depot;
    for(int i = 0; i < deliveries.size()-1; i++){
        for(int j = i+1; j < deliveries.size(); j++){
            if(distanceEarthMiles(comparing, deliveries[i].location) > distanceEarthMiles(comparing, deliveries[j].location)){
                DeliveryRequest temp = deliveries[i];
                deliveries[i] = deliveries[j];
                deliveries[j] = temp;
            }
        }
        comparing = deliveries[i].location;
    }
    newCrowDistance = calculatingDist(depot, deliveries);
}

//******************** DeliveryOptimizer functions ****************************

// These functions simply delegate to DeliveryOptimizerImpl's functions.
// You probably don't want to change any of this code.

DeliveryOptimizer::DeliveryOptimizer(const StreetMap* sm)
{
    m_impl = new DeliveryOptimizerImpl(sm);
}

DeliveryOptimizer::~DeliveryOptimizer()
{
    delete m_impl;
}

void DeliveryOptimizer::optimizeDeliveryOrder(
        const GeoCoord& depot,
        vector<DeliveryRequest>& deliveries,
        double& oldCrowDistance,
        double& newCrowDistance) const
{
    return m_impl->optimizeDeliveryOrder(depot, deliveries, oldCrowDistance, newCrowDistance);
}
