#include <stdio.h>
#include <stdlib.h>

typedef struct no { 
    int vizinho;
    struct no* proximaAresta;
} no;

typedef struct {
    const char* nacionalidade;
    const char* codigo;
} Pais;

Pais paises[] = {
    {"Afghans","1"},
    {"Albanians","2"},
    {"Algerians","3"},
    {"Andorrans","4"},
    {"Angolans","5"},
    {"Antiguans","6"},
    {"Argentinians","7"},
    {"Armenians","8"},
    {"Australians","9"},
    {"Austrians","10"},
    {"Azerbaijanis","11"},
    {"Bahamans","12"},
    {"Bahrainis","13"},
    {"Bangladeshis","14"},
    {"Barbadians","15"},
    {"Belarusians","16"},
    {"Belgians","17"},
    {"Belizeans","18"},
    {"Beninese","19"},
    {"Bhutanese","20"},
    {"Bolivians","21"},
    {"Bosnians","22"},
    {"Botswanans","23"},
    {"Brazilians","24"},
    {"Bruneians","25"},
    {"Bulgarians","26"},
    {"Burkinabes","27"},
    {"Burundians","28"},
    {"Cambodians","29"},
    {"Cameroonians","30"},
    {"Canadians","31"},
    {"CapeVerdeans","32"},
    {"CentralAfricans","33"},
    {"Chadians","34"},
    {"Chileans","35"},
    {"Chinese","36"},
    {"Colombians","37"},
    {"Comorians","38"},
    {"Congolese","39"},
    {"CostaRicans","40"},
    {"Croatians","41"},
    {"Cubans","42"},
    {"Cypriots","43"},
    {"Czechs","44"},
    {"Danes","45"},
    {"Djiboutians","46"},
    {"Dominicans","47"},
    {"Ecuadorians","48"},
    {"Egyptians","49"},
    {"Salvadorans","50"},
    {"EquatorialGuineans","51"},
    {"Eritreans","52"},
    {"Estonians","53"},
    {"Ethiopians","54"},
    {"Fijians","55"},
    {"Finns","56"},
    {"French","57"},
    {"Gabonese","58"},
    {"Gambians","59"},
    {"Georgians","60"},
    {"Germans","61"},
    {"Ghanaians","62"},
    {"Greeks","63"},
    {"Grenadians","64"},
    {"Guatemalans","65"},
    {"Guineans","66"},
    {"GuineaBissauans","67"},
    {"Guyanese","68"},
    {"Haitians","69"},
    {"Hondurans","70"},
    {"Hungarians","71"},
    {"Icelanders","72"},
    {"Indians","73"},
    {"Indonesians","74"},
    {"Iranians","75"},
    {"Iraqis","76"},
    {"Irish","77"},
    {"Israelis","78"},
    {"Italians","79"},
    {"Ivorians","80"},
    {"Jamaicans","81"},
    {"Japanese","82"},
    {"Jordanians","83"},
    {"Kazakhs","84"},
    {"Kenyans","85"},
    {"Kiribatians","86"},
    {"Kuwaitis","87"},
    {"Kyrgyz","88"},
    {"Laotians","89"},
    {"Latvians","90"},
    {"Lebanese","91"},
    {"Basotho","92"},
    {"Liberians","93"},
    {"Libyans","94"},
    {"Liechtensteiners","95"},
    {"Lithuanians","96"},
    {"Luxembourgers","97"},
    {"Malagasy","98"},
    {"Malawians","99"},
    {"Malaysians","100"},
    {"Maldivians","101"},
    {"Malians","102"},
    {"Maltese","103"},
    {"Marshallese","104"},
    {"Mauritanians","105"},
    {"Mauritians","106"},
    {"Mexicans","107"},
    {"Micronesians","108"},
    {"Moldovans","109"},
    {"Monacans","110"},
    {"Mongolians","111"},
    {"Montenegrins","112"},
    {"Moroccans","113"},
    {"Mozambicans","114"},
    {"Burmese","115"},
    {"Namibians","116"},
    {"Nauruans","117"},
    {"Nepalese","118"},
    {"Dutch","119"},
    {"NewZealanders","120"},
    {"Nicaraguans","121"},
    {"Nigeriens","122"},
    {"Nigerians","123"},
    {"NorthKoreans","124"},
    {"NorthMacedonians","125"},
    {"Norwegians","126"},
    {"Omanis","127"},
    {"Pakistanis","128"},
    {"Palauans","129"},
    {"Panamanians","130"},
    {"PapuaNewGuineans","131"},
    {"Paraguayans","132"},
    {"Peruvians","133"},
    {"Filipinos","134"},
    {"Poles","135"},
    {"Portuguese","136"},
    {"Qataris","137"},
    {"Romanians","138"},
    {"Russians","139"},
    {"Rwandans","140"},
    {"SaintLucians","141"},
    {"Salvadorans","142"},
    {"Samoans","143"},
    {"SanMarinese","144"},
    {"SaoTomeans","145"},
    {"Saudis","146"},
    {"Senegalese","147"},
    {"Serbians","148"},
    {"Seychellois","149"},
    {"SierraLeoneans","150"},
    {"Singaporeans","151"},
    {"Slovaks","152"},
    {"Slovenians","153"},
    {"SolomonIslanders","154"},
    {"Somalis","155"},
    {"SouthAfricans","156"},
    {"SouthKoreans","157"},
    {"SouthSudanese","158"},
    {"Spaniards","159"},
    {"SriLankans","160"},
    {"Sudanese","161"},
    {"Surinamese","162"},
    {"Swedes","163"},
    {"Swiss","164"},
    {"Syrians","165"},
    {"Taiwanese","166"},
    {"Tajiks","167"},
    {"Tanzanians","168"},
    {"Thais","169"},
    {"Timorese","170"},
    {"Togolese","171"},
    {"Tongans","172"},
    {"Trinidadians","173"},
    {"Tunisians","174"},
    {"Turks","175"},
    {"Turkmen","176"},
    {"Tuvaluans","177"},
    {"Ugandans","178"},
    {"Ukrainians","179"},
    {"Emiratis","180"},
    {"Britons","181"},
    {"Americans","182"},
    {"Uruguayans","183"},
    {"Uzbeks","184"},
    {"Vanuatuans","185"},
    {"Venezuelans","186"},
    {"Vietnamese","187"},
    {"Yemenis","188"},
    {"Zambians","189"},
    {"Zimbabweans","190"},
    {"Palestinians","191"},
    {"Vaticans","192"},
    {"Kosovars","193"}
};

const char* nomePais(const char* nacionalidade) {

    // Pego a quantidade de países que a gente tem
    int tamanho = sizeof(paises)/sizeof(paises[0]);

    for(int i = 0; i < tamanho; i++) {

        // Comparo se o que veio na nacionalidade, é o mesmo de algum do meu 
        // array de países, se for eu retorno o código, caso contrário eu retorno 0
        if(strcmp(nacionalidade, paises[i].nacionalidade) == 0)
            return paises[i].codigo;
    }

    return "0";
}


void adicionarAresta(int v, int w, no** adj) {
    no* n1 = malloc(sizeof(no));
    n1->vizinho = w;
    n1->proximaAresta = adj[v];
    adj[v] = n1;
}

void inicializarGrafo(no** adj, int n) {
    for(int i = 0; i < n; i++) {
        adj[i] = NULL;
    }
}

int main() {

}