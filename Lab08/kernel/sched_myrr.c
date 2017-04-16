#include "sched.h"
void init_myrr_rq (struct myrr_rq *rr_rq) {
	INIT_LIST_HEAD(&rr_rq->queue);
}	

static void enqueue_task_myrr(struct rq *rq, struct task_struct *p,
								int wakeup, bool head)
{
	struct sched_myrr_entity *myrr_se = &p->myrr;
	list_add_tail(&myrr_se->run_list, &rq->myrr.queue);
	printk(KERN_INFO"[SCHED_MYRR] ENQUEUE: Process-%d\n", p->pid);
}

static void dequeue_task_myrr(struct rq *rq,
								struct task_struct *p, int sleep)
{
	struct sched_myrr_entity *myrr_se = &p->myrr;
	list_del(&myrr_se->run_list);
	printk(KERN_INFO"[SCHED_MYRR] DEQUEUE: Process-%d\n", p->pid);
}

static void yield_task_myrr(struct rq *rq)
{
	struct sched_myrr_entity *myrr_se = &rq->curr->myrr;
	struct myrr_rq *myrr_rq = &rq->myrr;
	list_move_tail(&myrr_se->run_list, &myrr_rq->queue);
}

static void check_preempt_curr_myrr(struct rq *rq,
									struct task_struct *p, int flags)
{
	if (rq->curr->policy == SCHED_FIFO || rq->curr->policy == SCHED_RR)
	return ;
	if (rq->curr->policy == SCHED_MYRR)
	return ;
	/* preempt normal tasks */
	resched_task(rq->curr);
}

static struct task_struct *pick_next_task_myrr(struct rq *rq)
{
	struct sched_myrr_entity *myrr_se = NULL;
	struct task_struct *p = NULL;
	struct myrr_rq *myrr_rq = &rq->myrr;
	if (list_empty(&myrr_rq->queue))
	return NULL;
	myrr_se = list_entry(myrr_rq->queue.next,
	struct sched_myrr_entity,
	run_list);
	p = container_of(myrr_se, struct task_struct, myrr);
	return p;
}

static void put_prev_task_myrr(struct rq *rq, struct task_struct *p)
{
	/* it is the place to update the current task's
	* runtime statistics */
}

static void set_curr_task_myrr(struct rq *rq)
{
}

static void task_tick_myrr(struct rq *rq,
							struct task_struct *p, int queued)
{
	struct sched_myrr_entity *myrr_se = &rq->curr->myrr;
	if (p->policy != SCHED_MYRR) return ;
	
	if(--p->myrr.time_slice) 
		 return;
	
	
	p->myrr.time_slice = 10;
	list_move_tail(&myrr_se->run_list, &rq->myrr.queue);
	set_tsk_need_resched(p);	
}

unsigned int get_rr_interval_myrr(struct rq *rq,
									struct task_struct *p)
{
	/* ToDo: return a default timeslice */
	return 10;
}

static void prio_changed_myrr(struct rq *rq, struct task_struct *p,
								int oldprio, int running)
{
}

static void switched_to_myrr(struct rq *rq, struct task_struct *p,
							int running)
{
}

const struct sched_class myrr_sched_class = {
    .next = &fair_sched_class,
    .enqueue_task = enqueue_task_myrr,
    .dequeue_task = dequeue_task_myrr,
    .yield_task = yield_task_myrr,
    .check_preempt_curr = check_preempt_curr_myrr,
    .pick_next_task = pick_next_task_myrr,
    .put_prev_task = put_prev_task_myrr,



    .set_curr_task = set_curr_task_myrr,
    .task_tick = task_tick_myrr,
    .get_rr_interval = get_rr_interval_myrr,
    .prio_changed = prio_changed_myrr,
    .switched_to = switched_to_myrr,
};
