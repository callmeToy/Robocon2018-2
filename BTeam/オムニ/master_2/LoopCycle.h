/**
 *      @file   LoopCycle.h
 *      @brief  ループ周期の純粋仮想クラス
 *      @author 谷川　豊章
 *      @date   2016/9/1
 */

#ifndef DEF_LoopCycle_H
#define DEF_LoopCycle_H

#include <arduino.h>

/**     ループ周期の純粋仮想クラス
 */
class LoopCycle{
    
    const unsigned long CYCLE_US;   ///< 周期(unit:us)

public:

    /**     コンストラクタ
     *      @param  cycle_us    [in]目標のループ周期
     */
    LoopCycle(unsigned long cycle_us) : CYCLE_US(cycle_us)
    { }

    /**     デストラクタ
     */
    virtual ~LoopCycle() = 0;

    /**     ループ周期の読み出し
     *      @return ループ周期
     */
    unsigned long Cycle_us(){
        return CYCLE_US;
    }
    
};

LoopCycle::~LoopCycle(){}

#endif
