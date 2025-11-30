#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include "npc.h"
#include "bear.h"
#include "elf.h"
#include "bandit.h"


// Тесты создания NPC

TEST(NPCCreation, CreateBear) {
    Bear bear("TestBear", 100, 200);
    EXPECT_EQ(bear.type, BearType);
    EXPECT_EQ(bear.name, "TestBear");
    EXPECT_EQ(bear.x, 100);
    EXPECT_EQ(bear.y, 200);
}

TEST(NPCCreation, CreateElf) {
    Elf elf("TestElf", 150, 250);
    EXPECT_EQ(elf.type, ElfType);
    EXPECT_EQ(elf.name, "TestElf");
    EXPECT_EQ(elf.x, 150);
    EXPECT_EQ(elf.y, 250);
}

TEST(NPCCreation, CreateBandit) {
    Bandit bandit("TestBandit", 200, 300);
    EXPECT_EQ(bandit.type, BanditType);
    EXPECT_EQ(bandit.name, "TestBandit");
    EXPECT_EQ(bandit.x, 200);
    EXPECT_EQ(bandit.y, 300);
}


// Тесты сериализации/десериализации

TEST(Serialization, SaveAndLoadBear) {
    auto bear = std::make_shared<Bear>("SavedBear", 123, 456);
    
    std::stringstream ss;
    bear->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, BearType);
    
    Bear loaded(ss);
    EXPECT_EQ(loaded.name, "SavedBear");
    EXPECT_EQ(loaded.x, 123);
    EXPECT_EQ(loaded.y, 456);
}

TEST(Serialization, SaveAndLoadElf) {
    auto elf = std::make_shared<Elf>("SavedElf", 234, 567);
    
    std::stringstream ss;
    elf->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, ElfType);
    
    Elf loaded(ss);
    EXPECT_EQ(loaded.name, "SavedElf");
    EXPECT_EQ(loaded.x, 234);
    EXPECT_EQ(loaded.y, 567);
}

TEST(Serialization, SaveAndLoadBandit) {
    auto bandit = std::make_shared<Bandit>("SavedBandit", 345, 678);
    
    std::stringstream ss;
    bandit->save(ss);
    
    int type;
    ss >> type;
    EXPECT_EQ(type, BanditType);
    
    Bandit loaded(ss);
    EXPECT_EQ(loaded.name, "SavedBandit");
    EXPECT_EQ(loaded.x, 345);
    EXPECT_EQ(loaded.y, 678);
}


// Тесты расстояния

TEST(Distance, CloseNPCs) {
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 3, 4);
    
    EXPECT_TRUE(bear->is_close(elf, 10));
    EXPECT_TRUE(bear->is_close(elf, 5));
    EXPECT_FALSE(bear->is_close(elf, 4));
}

TEST(Distance, FarNPCs) {
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 100, 100);
    
    EXPECT_FALSE(bear->is_close(elf, 100));
    EXPECT_TRUE(bear->is_close(elf, 150));
}

TEST(Distance, SamePosition) {
    auto bear = std::make_shared<Bear>("Bear1", 50, 50);
    auto elf = std::make_shared<Elf>("Elf1", 50, 50);
    
    EXPECT_TRUE(bear->is_close(elf, 0));
    EXPECT_TRUE(bear->is_close(elf, 1));
}


// Тесты правил боя (Visitor Pattern)

TEST(FightRules, ElfKillsBandit) {
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    
    bool result = bandit->accept(elf);
    EXPECT_TRUE(result);
}

TEST(FightRules, ElfDoesNotKillElf) {
    auto elf1 = std::make_shared<Elf>("Elf1", 0, 0);
    auto elf2 = std::make_shared<Elf>("Elf2", 0, 0);
    
    bool result = elf2->accept(elf1);
    EXPECT_FALSE(result);
}

TEST(FightRules, ElfDoesNotKillBear) {
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    
    bool result = bear->accept(elf);
    EXPECT_FALSE(result);
}

TEST(FightRules, BanditKillsBandit) {
    auto bandit1 = std::make_shared<Bandit>("Bandit1", 0, 0);
    auto bandit2 = std::make_shared<Bandit>("Bandit2", 0, 0);
    
    bool result = bandit2->accept(bandit1);
    EXPECT_TRUE(result);
}

TEST(FightRules, BanditDoesNotKillElf) {
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    
    bool result = elf->accept(bandit);
    EXPECT_FALSE(result);
}

TEST(FightRules, BanditDoesNotKillBear) {
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    
    bool result = bear->accept(bandit);
    EXPECT_FALSE(result);
}

TEST(FightRules, BearKillsElf) {
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    
    bool result = elf->accept(bear);
    EXPECT_TRUE(result);
}

TEST(FightRules, BearDoesNotKillBear) {
    auto bear1 = std::make_shared<Bear>("Bear1", 0, 0);
    auto bear2 = std::make_shared<Bear>("Bear2", 0, 0);
    
    bool result = bear2->accept(bear1);
    EXPECT_FALSE(result);
}

TEST(FightRules, BearDoesNotKillBandit) {
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    
    bool result = bandit->accept(bear);
    EXPECT_FALSE(result);
}


// Тесты Observer Pattern

class TestObserver : public IFightObserver {
public:
    int fight_count = 0;
    int win_count = 0;
    int loss_count = 0;
    
    void on_fight(const std::shared_ptr<NPC> attacker, 
                  const std::shared_ptr<NPC> defender, bool win) override {
        (void)attacker;
        (void)defender;
        fight_count++;
        if (win)
            win_count++;
        else
            loss_count++;
    }
};

TEST(Observer, NotificationOnWin) {
    auto observer = std::make_shared<TestObserver>();
    
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
    
    elf->subscribe(observer);
    
    bandit->accept(elf);
    
    EXPECT_EQ(observer->fight_count, 1);
    EXPECT_EQ(observer->win_count, 1);
    EXPECT_EQ(observer->loss_count, 0);
}

TEST(Observer, NoNotificationOnLoss) {
    auto observer = std::make_shared<TestObserver>();
    
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    
    elf->subscribe(observer);
    
    bear->accept(elf);
    
    EXPECT_EQ(observer->fight_count, 0);
}

TEST(Observer, MultipleObservers) {
    auto observer1 = std::make_shared<TestObserver>();
    auto observer2 = std::make_shared<TestObserver>();
    
    auto bear = std::make_shared<Bear>("Bear1", 0, 0);
    auto elf = std::make_shared<Elf>("Elf1", 0, 0);
    
    bear->subscribe(observer1);
    bear->subscribe(observer2);
    
    elf->accept(bear);
    
    EXPECT_EQ(observer1->fight_count, 1);
    EXPECT_EQ(observer2->fight_count, 1);
}


// Тесты печати

TEST(Print, BearOutput) {
    Bear bear("TestBear", 100, 200);
    std::stringstream ss;
    bear.print(ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("bear") != std::string::npos);
    EXPECT_TRUE(output.find("TestBear") != std::string::npos);
    EXPECT_TRUE(output.find("100") != std::string::npos);
    EXPECT_TRUE(output.find("200") != std::string::npos);
}

TEST(Print, ElfOutput) {
    Elf elf("TestElf", 150, 250);
    std::stringstream ss;
    elf.print(ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("elf") != std::string::npos);
    EXPECT_TRUE(output.find("TestElf") != std::string::npos);
}

TEST(Print, BanditOutput) {
    Bandit bandit("TestBandit", 200, 300);
    std::stringstream ss;
    bandit.print(ss);
    
    std::string output = ss.str();
    EXPECT_TRUE(output.find("Bandit") != std::string::npos);
    EXPECT_TRUE(output.find("TestBandit") != std::string::npos);
}


// Интеграционные тесты

TEST(Integration, BattleScenario) {
    set_t npcs;
    
    npcs.insert(std::make_shared<Bear>("Bear1", 0, 0));
    npcs.insert(std::make_shared<Elf>("Elf1", 10, 0));
    npcs.insert(std::make_shared<Bandit>("Bandit1", 20, 0));
    
    EXPECT_EQ(npcs.size(), 3);
    
    set_t dead_list;
    for (const auto& attacker : npcs) {
        for (const auto& defender : npcs) {
            if ((attacker != defender) && (attacker->is_close(defender, 15))) {
                bool success = defender->accept(attacker);
                if (success)
                    dead_list.insert(defender);
            }
        }
    }
    
    EXPECT_GE(dead_list.size(), 1);
}

TEST(Integration, SaveAndLoadFile) {
    set_t original;
    original.insert(std::make_shared<Bear>("Bear1", 100, 200));
    original.insert(std::make_shared<Elf>("Elf1", 150, 250));
    original.insert(std::make_shared<Bandit>("Bandit1", 200, 300));
    
    std::string filename = "test_npc.txt";
    std::ofstream ofs(filename);
    ofs << original.size() << std::endl;
    for (auto& npc : original)
        npc->save(ofs);
    ofs.close();
    
    set_t loaded;
    std::ifstream ifs(filename);
    ASSERT_TRUE(ifs.is_open());
    
    int count;
    ifs >> count;
    EXPECT_EQ(count, 3);
    
    ifs.close();
    std::remove(filename.c_str());
}


// Краевые случаи

TEST(EdgeCases, EmptyName) {
    Bear bear("", 0, 0);
    EXPECT_EQ(bear.name, "");
}

TEST(EdgeCases, NegativeCoordinates) {
    Elf elf("Elf", -100, -200);
    EXPECT_EQ(elf.x, -100);
    EXPECT_EQ(elf.y, -200);
}

TEST(EdgeCases, LargeCoordinates) {
    Bandit bandit("Bandit", 10000, 20000);
    EXPECT_EQ(bandit.x, 10000);
    EXPECT_EQ(bandit.y, 20000);
}

TEST(EdgeCases, ZeroDistance) {
    auto bear = std::make_shared<Bear>("Bear", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    EXPECT_FALSE(bear->is_close(elf, 0));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
