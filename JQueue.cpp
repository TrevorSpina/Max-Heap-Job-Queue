// JQueue: a job queue using a max-heap and function pointers
// Based on MQueue by Scott Bennett (sb13@umbc.edu)
// CMSC 341, Spring 2019

#include "JQueue.h"

//
// JQueue implementations go here!!!!
//

JQueue::JQueue(int capacity, prifn_t priFn){
    m_capacity = capacity;
    priority = priFn;
    m_heap = new job_t[capacity];
    m_size = 0;
}

JQueue::~JQueue(){
    delete[] m_heap;
}

JQueue::JQueue(const JQueue& rhs){
    m_size = rhs.m_size;
    priority = rhs.priority;
    m_capacity = rhs.m_capacity;
    m_heap = new job_t[m_capacity];
    // make deep copy of each element in rhs heap
    for(int i = 0; i < rhs.m_size; i++){
        m_heap[i] = rhs.m_heap[i];
    }
}

JQueue& JQueue::operator=(const JQueue &rhs){
    m_size = rhs.m_size;
    priority = rhs.priority;
    m_capacity = rhs.m_capacity;
    delete[] m_heap;
    m_heap = new job_t[m_capacity];
    // make deep copy of each element in rhs heap
    for(int i = 0; i < rhs.m_size; i++){
        m_heap[i] = rhs.m_heap[i];
    }
    return *this;
}

void JQueue::insertJob(const job_t input){
    // insert job at the end of the queue
    m_heap[m_size] = input;
    // increment size
    m_size++;
    // index of the new job
    int index = m_size - 1;
    // index of the new job's parent
    int parentIndex = (index - 1)/2;
    // bubble up until priority of new job is higher than its children
    while(index > 0 && priority(m_heap[parentIndex]) <= priority(m_heap[index])){
        // swap parent and input
        swap(index, parentIndex);
        // bubble up to parent
        index = parentIndex;
        parentIndex = (index - 1)/2;
    }
}

job_t JQueue::getNextJob(){
    if(m_size > 1){
        // there is more than one job in queue
        // the highest priority job is first in the queue
        job_t nextJob = m_heap[0];
        // move each entry to the left in the array
        for(int i = 0; i < m_size - 1; i++){
            m_heap[i] = m_heap[i + 1];
        }
        // decrement size
        m_size--;
        buildHeap();
        return nextJob;
    }else{
        // decrement size
        m_size--;
        return m_heap[0];
    }
}

int JQueue::numJobs() const {
    return m_size;
}

void JQueue::printJobQueue() const{
    std::cout << "Job Queue Size: " << m_size << std::endl;
    std::cout << "Number of jobs in the queue: " << m_size << std::endl;
    for(int i = 0; i < m_size; i++){
        std::cout
        << "["  << i + 1 << "] "
        << m_heap[i] << " (" << priority(m_heap[i]) << ")"
        << std::endl;
    }
}
prifn_t JQueue::getPriorityFn(){
    return priority;
}

void JQueue::setPriorityFn(prifn_t priFn){
    // set new priority function
    priority = priFn;
    // rebuild the heap with the new priority function
    buildHeap();
}

void JQueue::dump() const{
    // print out entire heap
    for(int i = 0; i < m_capacity; i++){
        std::cout << m_heap[i] << std::endl;
    }
}

void JQueue::buildHeap(){
    // build the heap by calling maxHeapify on each element with children
    for(int i = m_size / 2 - 1; i >= 0; i--){
        maxHeapify(i);
    }
}
void JQueue::maxHeapify(int index){
    // set left and right indices
    int left = 2 * index + 1;
    int right = left + 1;
    // check both children exist for index
    if(right < m_size && left < m_size){
        // index has 2 children
        if((priority(m_heap[index]) <= priority(m_heap[right])) ||
           (priority(m_heap[index]) <= priority(m_heap[left]))){
            if(priority(m_heap[left]) <= priority(m_heap[right])){
                if(priority(m_heap[index]) == priority(m_heap[right])){
                    // swap if priority of index is the same as the right child
                    swap(right, index);
                }else{
                    // swap right child with index if it is greater
                    swap(right, index);
                    // bubble down
                    maxHeapify(right);
                }
            }else if(priority(m_heap[right]) < priority(m_heap[left])){
                if(priority(m_heap[index]) == priority(m_heap[left])){
                    // swap if priority of index is the same as the left child
                    swap(left, index);
                }else{
                    // swap left child with index if it is greater
                    swap(left, index);
                    // bubble down
                    maxHeapify(left);
                }
            }
        }
    }else if(left < m_size){
        // index only has left child
        if(priority(m_heap[index]) <= priority(m_heap[left])){
            if(priority(m_heap[index]) == priority(m_heap[left])){
                // swap if priority of index is the same as the left child
                swap(left, index);
            }
            // swap left child with index if it is greater
            swap(left, index);
            // bubble down
            maxHeapify(left);
        }
    }else if(right < m_size){
        if(priority(m_heap[index]) == priority(m_heap[right])){
            // swap if priority of index is the same as the right child
            swap(right, index);
        }
        // index only has right child
        if(priority(m_heap[index]) <= priority(m_heap[right])){
            // swap right child with index if it is greater
            swap(right, index);
            // bubble down
            maxHeapify(right);
        }
    }
}

void JQueue::swap(int index1, int index2){
    job_t temp1 = m_heap[index1];
    m_heap[index1] = m_heap[index2];
    m_heap[index2] = temp1;
}

// Overloaded insertion operator for job_t
std::ostream& operator<<(std::ostream& sout, const job_t& job)
{
    sout << "Job: " << job.m_name << ", pri: " << job.m_priority
    << ", u: " << job.m_user << ", g: " << job.m_group << ", proc: "
    << job.m_proc << ", mem: " << job.m_mem << ", time: " << job.m_time;
    return sout;
}

