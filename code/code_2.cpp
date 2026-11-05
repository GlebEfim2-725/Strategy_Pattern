#include <iostream>
#include <memory>
#include <ctime>
using namespace std;

class BossAttack{
    public:
virtual ~BossAttack()=default;
virtual int attack(string boss_name)=0;
};

class BossAttackKnife:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" atakuje magicznym scyzorykiem.\n";
    return 11;
}
};

class BossAttackMachete:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" tnie twoja plec zalodowala macheta.\n";
    return 17;
}
};

class BossAttackChook:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" chce nasadzic ciebie na haczyk.\n";
    return 22;
}
};

class BossAttackBones:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" rzuca eksplodujace rybie osci.\n";
    return 25;
}
};

class BossAttackFangs:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" wysyla na ciebie wicher z kocich klow.\n";
    return 28;
}
};

class BossAttackEggs:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" wywoluje deszcz z trujacych jajkogranatow.\n";
    return 33;
}
};

class BossAttackInjection:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" laduje kalasznikowa strzykawkami z fairy. Ktos bedzie czysty.\n";
    return 38;
}
};

class BossAttackLegion:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" wzywa na pole walki upadlych rzymskich legionerow.\n";
    return 42;
}
};

class BossAttackTatar:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" sciaga najazd tatarow, ktore otaczaja ciebie ze wszystkich stron.\n";
    return 46;
}
};

class BossAttackArmastorm:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" stwarza ksiezyc, ktory strzela promieniowaniem gamma.\n";
    return 82;
}
};

class SetBossAttack{
    public:
virtual ~SetBossAttack()=default;
virtual unique_ptr<BossAttack> setNewAttack()=0;
};

class SetBossAttack1:public SetBossAttack{public:
unique_ptr<BossAttack> setNewAttack() override{
    int a=rand()%10;
    if(a<7){
    return make_unique<BossAttackKnife>();}
    else if(a!=9){
        return make_unique<BossAttackMachete>();}
else{
    return make_unique<BossAttackChook>();
}}
};

class SetBossAttack2:public SetBossAttack{public:
unique_ptr<BossAttack> setNewAttack() override{
    int a=rand()%10;
    if(a<3){
    return make_unique<BossAttackChook>();}
    else if(a<7){
        return make_unique<BossAttackBones>();}
else if(a<9){
    return make_unique<BossAttackFangs>();
}else{
    return make_unique<BossAttackEggs>();
}}
};

class SetBossAttack3:public SetBossAttack{public:
unique_ptr<BossAttack> setNewAttack() override{
    int a=rand()%20;
    if(a<9){
    return make_unique<BossAttackInjection>();}
    else if(a<14){
        return make_unique<BossAttackLegion>();}
else if(a<19){
    return make_unique<BossAttackTatar>();
}else{
    return make_unique<BossAttackArmastorm>();
}}
};

class Boss{
    private:
    unique_ptr<BossAttack>attack_strategy_;
    unique_ptr<SetBossAttack>set_attack_strategy_=make_unique<SetBossAttack1>();
    string boss_name;
    string full_boss_name;
    int health=500;
    int max_health=500;
    short boss_phase=1;
    
void setAttack(){
    attack_strategy_=set_attack_strategy_->setNewAttack();
}
    
public:   
int attack(){setAttack();
             int damage=attack_strategy_->attack(boss_name);
             cout<<boss_name<<" uderza z sila "<<damage<<"! Zdrowie bossa wynosi "<<health<<".\n";
return damage;
}
    
    string getBossName(){ return boss_name; }
    
    Boss(string name, string name2){boss_name=name; full_boss_name=name2;
                      string intro="\tSzedles przez pole, gdy ujzalesz nieznajomego. Figura w czarnym siedziala na kamieniu i grzebala palcami miedzy trawinkami. Wydawalo sie, iz ona nie zauwazyla ciebie, jednak to byla wielka zmylka.\n\tKiegy podszedles blizej, mezczyzna nawet nie drgnal.\n - Nie mow ani slowa. Przestraszysz go. - zagadal on do ciebie, nawet nie spojrzawszy.\n - Kogo? - pospieszyles zapytac.\n - Prosilem przeciez nie wydawac ani dzwieku... - zasyczal on - Nie, ja wymagalem absolutnego milczenia!\n\tCzlowiek wskoczyl i rzucil sie do ataku.";
                     cout<<intro<<endl<<endl;}

    void hurt(int damage){
        if(damage==0){return;}
        switch (boss_phase){
            case 1:{
            health-=damage; 
                if(health<0.7*max_health){boss_phase=2; set_attack_strategy_=make_unique<SetBossAttack2>(); max_health=0.7*max_health;   
cout<<boss_name<<" dostaje ataku wscieklizny. Walka staje sie coraz krwawsza.\n";} 
                break;}
            case 2:{
            health-=5+damage*0.6;
                if(health<0.4*max_health){boss_phase=3; set_attack_strategy_=make_unique<SetBossAttack3>(); max_health=0.4*max_health;
boss_name=full_boss_name;                                 
cout<<"Zebys wiedzial, z kim masz sprawe, tak naprawde zwa mnie "<<boss_name<<". Ahaaahahahahahaha!!!\n"<<boss_name<<" spiewa piosenki o twojej smierci.\n";}
                break;}
            case 3:{
            health-=7+damage*0.2; break;}
        }

    }
    int getHealth(){
        return health;
    }
    void fall(){
        string ending="\t"+boss_name+" upadl na kolana. Oczy Barona zalali sie krwia i byly napelnione wskieklosci.\n - Nigdy mnie nie zwyciezysz. Jestes jedynie czlowiekiem - "+boss_name+" sie zasmial - twoj koniec jest niedaleko. Oczekuj.\n\t"+boss_name+" obrocil sie w klebek czarnego dymu i znikl, nie zdazyles nawet mrugnac oczami.\n\tPoszedl deszcz.\n\n>>> Koniec gry.";
        cout<<ending;
    }
};

class Player{
    private:
    int health=100;
    int protection=0;
    int regeneration_time=5;
    bool is_dodging=0;
    public:
    void hurt(int damage){
        protection--;
        regeneration_time--;
        if(protection>-1){
            cout<<">>> Ataka przeciwnika zostala zablokowana. Mozesz zablokowac jescze "<<protection<<" atakow przeciwnika.\n\n";
        }else if(is_dodging==true){
            is_dodging=false;
            if(rand()%3==0){
                cout<<"Calkowicie omineles atak przeciwnika.\n\n";
            }else{
                health-=damage*0.5;
                if (health<0){health=0;}
                cout<<"Dostajesz polowe obrazen. Twoje zdrowie wynosi "<<health<<".\n\n";
            }
        }
        else{
        health-=damage;
            if (health<0){health=0;}
            cout<<">>> Zostales zraniony. Twoje zdrowie wynosi "<<health<<".\n\n";
        }
    }
    Player(){
        cout<<">>> Jestes gotow do boju.\n\n";
    }
    int getHealth(){
        return health;
    }
    void fall(){
        string ending="\tCierpisz porazke w bitwie z nieznajomym. Przed koncem zauwazasz malego skreconego jezyka u swoich nog.\n\n>>> Koniec gry.";
        cout<<ending;
    }
    int attack(){
        int attack_damage=rand()%15+16;
        cout<<">>> Nanosisz "<<attack_damage<<" obrazen!\n";
        return attack_damage;
    }
    int protect(){
        if(rand()%5!=0){
            protection=1; 
            cout<<">>> Ustawiasz blok.\n";
            return 0;
        }else{
            cout<<">>> Zasloniles sie tarcza. Jestes odporny na 3 ataki przeciwnika.\n";
            protection=3; return 0;
        }
    }
    int heal(){
        health+=(100-health)*0.8;
        regeneration_time=5;
        if(health>100){
            health=100;
        }
        cout<<">>> Masz teraz "<<health<<" zywotnosci.\n";
        return 0;
    }
    int dodge(){
        is_dodging=1;
        cout<<">>> Probojesz uniknac kolejnego ciosu.\n";
        return 0;
    }
    int behawioral(){
        while(true){
            int a;
            cout<<">>> Jak sie zachowasz: [1 - atak; 2 - unik; 3 - obrona; 4 - leczenie]\t";
        cin>>a;
            if(a==1){
                return attack();
            }else if(a==2){if(protection<=0){
                return dodge();
            }else{
                cout<<"Nie mozesz zrobic uniku, gdy zaslaniasz sie tarcza.\n";
            }
            }else if(a==3){if(protection<0){
                return protect();}
                   else{if(protection!=0){
                       cout<<"Nie mozesz stosowac obrony, gdy masz tarcze.\n";}
                   else{ cout<<"Nie mozesz stosowac teraz obrony, bo jestes wykonczony. Sproboj w nastepnym ruchu.\n";}}
            }else if(a==4){if(regeneration_time<1){
                return heal();}else{
                cout<<"Mozesz skorzystac z leczenia dopiero za "<<regeneration_time<<" tury.\n";
                }
            }
    }
    }
};

int main(){
Boss Gleb("Gleb","Baron Gleb II von Allegart");
Player sb;
    srand(time(0));
while(true){
    if(sb.getHealth()>0){
Gleb.hurt(sb.behawioral());
        
    if(Gleb.getHealth()>0){
sb.hurt(Gleb.attack());   
}else{Gleb.fall();return 0;}
        
}else{sb.fall();return 0;}    

    
}
    
}