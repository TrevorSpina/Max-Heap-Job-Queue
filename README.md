# Max-Heap-Job-Queue
# Introduction
On High Performance Computing (HPC) clusters, there is typically greater demand for compute resources than can be met at any one time. The job management system maintains a queue of submitted compute jobs and determines which jobs can be run based on policy set by the administrators. For example, a compute job that requires a small number of processors, say 16, and is expected to run for only a few minutes, might be prioritized ahead of a job that requires many processors and hours or days to run. On the other hand, there may be times (e.g. times of lower demand such as nighttime or over school breaks) where the resource-intensive jobs are given priority. Therefore, the job queue must be very flexible and able to support a wide range of prioritization functions.

In this project, you will implement a job queue class (JQueue) based on a max-heap data structure; it will maintain a max-heap based on the computed priority of each job, where the priority function is provided to the JQueue constructor via a function pointer. Inserting to and extracting from the max-heap requires “bubbling up ” or “bubbling down” to maintain the max-heap property; the comparisons that are part of the “bubbling” process will be made on the computed priorities of jobs in the heap. In addition, if the prioritization function is changed, the heap must be rebuilt, which also requires using the appropriate “bubbling” method.

For the purposes of this project, compute jobs have the following attributes (defined in JQueue.h) that can be used by the prioritization function:
Job Name
A descriptive name; not useful for prioritization.
Priority
A user-specified priority in the range 1–100. This should not be confused with the computed priority, which takes the user-specified priority and other job attributes into account.
User
A user id in the range 0–100. The computed priority may depend on the user id.
Group
A group id in the range 0–100. Groups could represent different research groups or funding sources.
Proc
The number of processors required by the job, in the range 1–255.
Mem
Memory requirements per processor in number of Mb. The range is 1–65536 (1 Mb - 64 Gb).
Time
Maximum wallclock time required, in seconds. The range is 1–172,800 (1 second - 48 hours).
