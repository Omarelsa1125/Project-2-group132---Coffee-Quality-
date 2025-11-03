#include "functions.h"
#include <string>
#include <random>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
using namespace std;


void CoffeeManager::generate(int n) {
    data.clear();
    data.reserve(n);
    random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> scoreDist(0.0, 10.0);


    const vector<string> countries = {
        "Angola", "Bolivia", "Brazil", "Burundi", "Cameroon", "Central African Republic",
         "Colombia", "Congo", "Costa Rica", "Cuba", "Democratic Republic of Congo",
         "Dominican Republic", "East Timor", "Ecuador", "El Salvador", "Equatorial Guinea",
         "Ethiopia", "Fiji", "Gabon", "Ghana", "Guatemala", "Guinea", "Haiti", "Honduras",
         "India", "Indonesia", "Ivory Coast", "Jamaica", "Kenya", "Laos", "Liberia",
         "Madagascar", "Malawi", "Mauritania", "Mexico", "Nicaragua", "Nigeria", "Panama",
         "Papua New Guinea", "Paraguay", "Peru", "Rwanda", "Sao Tome and Principe",
         "Sierra Leone", "Tanzania", "Thailand", "Togo", "Trinidad and Tobago", "Uganda",
         "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"
    };
    const vector<string> regions = {
       // Ethiopia (birthplace of coffee)
        "Yirgacheffe", "Sidamo", "Guji", "Limmu", "Harrar", "Gambela", "Bench Maji",
        // Colombia
        "Huila", "Nariño", "Cauca", "Antioquia", "Cundinamarca", "Quindío", "Risaralda",
        // Kenya
        "Nyeri", "Kirinyaga", "Kiambu", "Murang'a", "Embu", "Meru", "Machakos",
        // Brazil
        "Minas Gerais", "São Paulo", "Espírito Santo", "Bahia", "Cerrado Mineiro",
        "Mogiana", "Sul de Minas", "Matas de Minas", "Chapada Diamantina",
        // Guatemala
        "Antigua", "Huehuetenango", "Atitlán", "Acatenango", "Cobán", "Nueva Oriente",
        // Costa Rica
        "Tarrazú", "Tres Ríos", "Orosi", "Cumbres del Poás", "Turrialba", "Brunca",
        // Indonesia
        "Sumatra", "Java", "Sulawesi", "Flores", "Bali", "Timor", "Toraja",
        // Vietnam
        "Central Highlands", "Da Lat", "Buon Ma Thuot", "Dong Nai", "Lam Dong",
        // Honduras
        "Copán", "Santa Barbara", "El Paraíso", "Ocotepeque", "La Paz", "Intibucá",
        // Peru
        "Cajamarca", "Cusco", "Puno", "Junín", "Pasco", "Ayacucho", "Chanchamayo",
        // India
        "Karnataka", "Kerala", "Tamil Nadu", "Coorg", "Chikmagalur", "Araku Valley",
        // Mexico
        "Chiapas", "Veracruz", "Oaxaca", "Puebla", "Guerrero", "Jalisco",
        // Nicaragua
        "Jinotega", "Matagalpa", "Nueva Segovia", "Madriz", "Estelí",
        // Tanzania
        "Arusha", "Mbeya", "Ruvuma", "Rungwe", "Mbinga", "Kigoma",
        // Uganda
        "Mount Elgon", "Bugisu", "Rwenzori", "Kigezi", "Elnon",
        // Rwanda
        "Gakenke", "Nyamasheke", "Gasabo", "Karongi", "Nyabihu",
        // Papua New Guinea
        "Eastern Highlands", "Western Highlands", "Baiyer", "Wahgi Valley",
        // Jamaica
        "Blue Mountains", "Yallahs", "St. Andrew",
        // Yemen
        "Haraz", "Matari", "Sana'a",
        // Others
        "Kona", "Ka'u", "Puna", "Hamaoina", "Ka'u", "Ollantaytambo", "Vilcabamba",
        "Chimborazo", "Loja", "Manabí", "Galapagos", "Kauai", "Maui", "Oahu"
    };
    const vector<string> owners = {
        "Kona Pacific Farmers Cooperative", "Finca La Bella", "Onyx Coffee Lab",
         "Blue Bottle Coffee", "Intelligentsia Coffee", "Stumptown Coffee Roasters",
         "Counter Culture Coffee", "Verve Coffee Roasters", "La Colombe Coffee Roasters",
         "Heart Coffee Roasters", "Sightglass Coffee", "Ritual Coffee Roasters",
         "Four Barrel Coffee", "Coava Coffee Roasters", "Happy Mug Coffee",
         "Finca Deborah", "Hacienda La Esmeralda", "Finca El Injerto", "Café Don Gato",
         "Molinos de Honduras", "Café San Agustín", "CoopeTarrazú", "Café Britt",
         "Doka Estate", "Finca Rosa Grande", "PT. Gunung Agung", "Mandheling Estate",
         "Tobias Estate", "Kahawa 1893", "Kew Gardens", "Timor Estate", "Alta Verapaz Co-op",
         "Café de Altura", "Finca Kilimanjaro", "Karingani Farmers Co-op", "Rutuma Estate",
         "Kieni Farmers Co-op", "Gatugi Farmers Group", "Finca Santa Isabel", "Hacienda Aquiares",
         "Café Los Volcanes", "PT. Koperasi Tani", "Dalat Highland", "Buon Me Thuot Co-op",
         "Finca El Carmen", "Marcala Co-op", "Apaneca-Ilamatepec", "Finca El Sauce",
         "Cusco Co-op", "Chanchamayo Valley", "Coorg Growers Co-op", "Araku Valley Farmers",
         "Chiapas Co-op", "Veracruz Estate", "Jinotega Co-op", "Matagalpa Farmers",
         "Arusha Coffee Co-op", "Mbeya Farmers Group", "Mount Elgon Co-op", "Gakenke District Co-op"
    };

    uniform_int_distribution<> cDist(0, countries.size() - 1);
    uniform_int_distribution<> rDist(0, regions.size() - 1);
    uniform_int_distribution<> oDist(0, owners.size() - 1);

    for (int i = 0; i < n; ++i) {
        Coffee c;
        c.country = countries[cDist(gen)];
        c.region  = regions[rDist(gen)];
        c.owner   = owners[oDist(gen)];

        auto randScore = [&]() { return round(scoreDist(gen) * 100.0) / 100.0; };

        c.aroma       = randScore();
        c.flavor      = randScore();
        c.aftertaste  = randScore();
        c.acidity     = randScore();
        c.body        = randScore();
        c.balance     = randScore();
        c.uniformity  = randScore();
        c.sweet       = randScore();
        c.moisture    = randScore();

        // TOTAL = SUM OF ALL 9 SCORES
        c.total = c.aroma + c.flavor + c.aftertaste + c.acidity +
                  c.body + c.balance + c.uniformity + c.sweet + c.moisture;
        c.total = std::round(c.total * 100.0) / 100.0;

        data.push_back(c);
    }
}

void CoffeeManager::calculateQualityScore(std::vector<Coffee>& data) {
    for (auto& coffee : data) {
        double qualityScoreSum = coffee.aroma + coffee.flavor + coffee.aftertaste +
            coffee.acidity + coffee.body + coffee.balance + coffee.uniformity + coffee.sweet + coffee.moisture;
        coffee.total = qualityScoreSum / 9.0;
    }
}

std::vector<Coffee>& CoffeeManager::getData() {
    return data;
}
void CoffeeManager::merge(vector<Coffee>& arr, int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Coffee> L(n1);
    vector<Coffee> R(n2);
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2){
        if (L[i].total >= R[j].total)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}
void CoffeeManager::mergeSort(vector<Coffee>& arr, int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
vector<Coffee> CoffeeManager::getTopN(int n){
    vector<Coffee> copy = data;
    if (copy.empty()) return {};
    mergeSort(copy, 0,copy.size() - 1);
    if(n > copy.size()) n = copy.size();
    return vector<Coffee>(copy.begin(), copy.begin() + n);
}

vector<Coffee> CoffeeManager::getBottomN(int n){
    vector<Coffee> copy = data;
    if(copy.empty()) return {};
    mergeSort(copy, 0, copy.size() - 1);
    if (n > copy.size()) n = copy.size();
    return vector<Coffee>(copy.end() - n, copy.end());
}











