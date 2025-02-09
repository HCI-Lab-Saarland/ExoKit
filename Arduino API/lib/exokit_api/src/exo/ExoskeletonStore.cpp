#include "ExoskeletonStore.h"

ExoskeletonStore* ExoskeletonStore::instance{};

ExoskeletonStore &ExoskeletonStore::getInstance() {
    if(!instance) {
        instance = new ExoskeletonStore();
    }
    return *instance;
}

ExoskeletonHandle* ExoskeletonStore::getById(int8_t id) {
    for(int i{0}; i < exos.size(); i++) {
        exoskeleton_store_entry_t* entry = exos.get(i);
        if(entry->id != id) {
            continue;
        }
        return &entry->exo;
    }
    return nullptr;
}

ExoskeletonStore::ExoskeletonStore():
    exos(LinkedList<exoskeleton_store_entry_t*>()) {}

int8_t ExoskeletonStore::add(ExoskeletonHandle &exo) {
    int8_t maxId{};
    for(int i{0}; i < exos.size(); i++) {
        exoskeleton_store_entry_t* entry = exos.get(i);
        maxId = max(maxId, entry->id);
    }
    maxId++;
    exos.add(new exoskeleton_store_entry_t {
        exo, maxId
    });
    exo.setId(maxId);
    return maxId;
}
