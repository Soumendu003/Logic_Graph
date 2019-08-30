#include"Name_to_ID_Map.h"

using namespace std;

int main(){
    Name_to_ID_Map map(2);
    map.update("Guddu",1);
    map.update("Hazard",2);
    map.update("Kante",3);
    cout<<"ID of Guddu = "<<map.get_ID("Guddu")<<endl;
    cout<<"ID of Hazard = "<<map.get_ID("Hazard")<<endl;
    cout<<"ID of Kante = "<<map.get_ID("Kante")<<endl;
    return 0;
}