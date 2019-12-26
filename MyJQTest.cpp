// JQueue: a job queue using a max-heap and function pointers
// Based on MQueue by Scott Bennett (sb13@umbc.edu)
// CMSC 341, Spring 2019

#include "JQueue.h"

//
// Priority functions compute an integer priority for a job.  Internal
// computations may be floating point, but must return an integer.
//
// Function definitions are below main()
//

int function1(const job_t &job);
int function2(const job_t &job);
int function3(const job_t &job);

int main() {
    
    
    JQueue jobQueue1(25, function1);
    JQueue jobQueue2(25, function2);
    
    job_t job1("job1", 84, 3, 19,  32, 128, 240);
    job_t job2("job2", 20, 59,  78, 128,  2048, 3600);
    job_t job3("job3", 8, 34, 12, 28, 1536, 1900);
    job_t job4("job4", 55, 38, 19,  64, 1024, 120);
    job_t job5("job5", 10, 34, 46,  8, 256, 24);
    job_t job6("job6", 46, 3, 19,  64, 512, 240);
    job_t job7("job7", 14, 54,  9, 32,  512, 790);
    job_t job8("job8", 66, 34, 12, 64, 1536, 2400);
    job_t job9("job9", 32, 38, 19,  64, 1024, 120);
    job_t job10("job10", 10, 36, 46,  8, 256, 24);
    job_t job11("job11", 26, 3, 19,  64, 512, 240);
    job_t job12("job12", 20, 59,  78, 16,  64, 30);
    job_t job13("job13", 2, 34, 12, 128, 64, 1450);
    job_t job14("job14", 47, 38, 19,  23, 32, 25);
    job_t job15("job15", 93, 34, 46,  8, 256, 24);
    job_t job16("job16", 57, 3, 19,  64, 512, 240);
    job_t job17("job17", 23, 59,  78, 128,  2048, 2300);
    job_t job18("job18", 25, 64, 12, 128, 1536, 2400);
    job_t job19("job19", 51, 38, 19,  64, 1024, 120);
    job_t job20("job20", 17, 32, 46,  8, 256, 24);
    job_t job21("job21", 91, 3, 19,  64, 512, 240);
    job_t job22("job22", 2, 59,  43, 128,  1024, 4500);
    job_t job23("job23", 8, 31, 12, 128, 1536, 2400);
    job_t job24("job24", 50, 8, 19,  64, 2048, 1440);
    job_t job25("job25", 10, 39, 56,  8, 256, 24);
    
    
    std::cout << "=== insert jobs ===" << std::endl;
    
    jobQueue1.insertJob(job1);
    jobQueue1.insertJob(job2);
    jobQueue1.insertJob(job3);
    jobQueue1.insertJob(job4);
    jobQueue1.insertJob(job5);
    jobQueue1.insertJob(job6);
    jobQueue1.insertJob(job7);
    jobQueue1.insertJob(job8);
    jobQueue1.insertJob(job9);
    jobQueue1.insertJob(job10);
    jobQueue1.insertJob(job11);
    jobQueue1.insertJob(job12);
    jobQueue1.insertJob(job13);
    jobQueue1.insertJob(job14);
    jobQueue1.insertJob(job15);
    jobQueue1.insertJob(job16);
    jobQueue1.insertJob(job17);
    jobQueue1.insertJob(job18);
    jobQueue1.insertJob(job19);
    jobQueue1.insertJob(job20);
    jobQueue1.insertJob(job21);
    jobQueue1.insertJob(job22);
    jobQueue1.insertJob(job23);
    jobQueue1.insertJob(job24);
    jobQueue1.insertJob(job25);
    
    //jobQueue1.setPriorityFn(function1);
    jobQueue1.printJobQueue();
    
    std::cout << "=== change priority function (heap should rebuild) ===" << std::endl;
    
    jobQueue1.setPriorityFn(function2);
    
    jobQueue1.printJobQueue();
    
    std::cout << "=== test assignment operator ===" << std::endl;
    
    jobQueue2 = jobQueue1;
    
    jobQueue2.printJobQueue();
    
    std::cout << "=== test copy constructor ===" << std::endl;
    
    JQueue jobQueue3 = jobQueue2;

    jobQueue3.printJobQueue();
    
    std::cout << "\nFinal queue in priority order:\n";
    while (jobQueue3.numJobs() > 0) {
        job_t job = jobQueue3.getNextJob();
        std::cout << job << " (" << jobQueue3.getPriorityFn()(job) << ")" << std::endl;
    }
    
    return 0;
}

int function1(const job_t &job) {
    float pri;
    
    pri = 4 * job.m_priority;
    
    // If user is less than 49 add 400
    if (job.m_user > 49) pri += 500;
    
    pri += 200;
    
    // If group is even add 400
    if (job.m_group % 2 == 0) pri += 400;
    
    pri -= job.m_proc + 0.001 * job.m_mem + 0.001 * job.m_time;
    
    return int(pri);
}

int function2(const job_t &job) {
    float pri;
    
    pri = job.m_priority;
    
    pri += 100 - job.m_user;
    
    // If group is less than 10 add 200
    if (job.m_group < 10) pri += 200;
    
    pri -= 0.0005 * (job.m_time + job.m_proc + job.m_mem);
    
    return int(pri);
}
