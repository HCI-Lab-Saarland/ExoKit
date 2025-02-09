#ifndef CHI25_EXOSKELETON_API_EXOSKELETONSTORE_H
#define CHI25_EXOSKELETON_API_EXOSKELETONSTORE_H


#include "LinkedList.h"
#include "ExoskeletonHandle.h"

class ExoskeletonStore {
public:
    struct exoskeleton_store_entry_t {
        ExoskeletonHandle& exo;
        int8_t id;
    };
private:

    static ExoskeletonStore* instance;
    LinkedList<exoskeleton_store_entry_t*> exos;
    ExoskeletonStore();

public:
    static ExoskeletonStore& getInstance();
    /**
     * Retrieves an ExoskeletonHandle by its unique ID.
     * @param id The unique identifier of the exoskeleton.
     * @return Pointer to the ExoskeletonHandle.
     */
    ExoskeletonHandle* getById(int8_t id);


    /**
     * Adds a new ExoskeletonHandle to the store and assigns it a unique ID.
     * 
     * @param exo Reference to the ExoskeletonHandle to be added.
     * @return The assigned unique ID of the added exoskeleton.
     */
    int8_t add(ExoskeletonHandle& exo);

};


#endif //CHI25_EXOSKELETON_API_EXOSKELETONSTORE_H
