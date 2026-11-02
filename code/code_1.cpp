#include <iostream>
#include <memory>
using namespace std;

class BossAttack{
    public:
virtual ~BossAttack()=default; //деконструктор в стратегии должен быть обязательно
virtual int attack(string boss_name)=0; //функция будет требовать перезаписи
};

class BossAttackKnife:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" атакует магическим кинжалом!"<<endl;
    return 30;
}
};

class BossAttackMachete:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" режет вашу плоть заледеневшим тесаком."<<endl;
    return 60;
}
};

class BossAttackBones:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" метает заминированные рыбные кости."<<endl;
    return 200;
}
};

class BossAttackDance:public BossAttack{public:
int attack(string boss_name) override{
    cout<<boss_name<<" танцует брейк-данс на надгробии вашего дедушки."<<endl;
    return 0;
}
};



class Boss{
    private:
    unique_ptr<BossAttack>attack_strategy_;//это указатель на стратегию
    public:
    string boss_name;
void setAttack(unique_ptr<BossAttack>new_attack_strategy){
    attack_strategy_=std::move(new_attack_strategy);
}//метод изменения стратегии.
int attack(){
    if(attack_strategy_){
        return attack_strategy_->attack(boss_name);//класс->атака. Можно (*attack_strategy_).attack(boss_name);
    }else{
        cout<<boss_name<<" пьёт молоко."<<endl;
        return 0;
    }
}
};

int main(){
Boss Gleb;
Gleb.boss_name="Барон Глеб II вон Аллегарт";//ну как же без столь прекрасного имени?
int your_health=300;

Gleb.setAttack(make_unique<BossAttackMachete>());//установка класса обращения.
your_health-=Gleb.attack();

Gleb.setAttack(make_unique<BossAttackBones>());
your_health-=Gleb.attack();

Gleb.setAttack(make_unique<BossAttackDance>());
your_health-=Gleb.attack();

if (your_health<0){
cout<<"После долгих раздумий "<<Gleb.boss_name<<" решил отправить вас на службу османскому султану."<<endl;
}else{
cout<<"Ваше здоровье составило "<<your_health<< " после того, как вы выпили этот подозрительный чай с ромашкой."<<endl;}
return 0;
}