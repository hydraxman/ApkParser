package com.bushaopeng.android.parseapk;


import com.bushaopeng.android.parseapk.base.DexDataItem;
import com.bushaopeng.android.parseapk.utils.Utils;

/**
 * Created by bsp on 17/3/18.
 */
public class IntRefsItem extends DexDataItem<Integer, String> {
    public IntRefsItem(String name) {
        super(name);
    }

    @Override
    protected Integer[] createRefs() {
        return new Integer[count];
    }

    @Override
    protected int getRefSize() {
        return Integer.SIZE / Byte.SIZE;
    }


    protected Integer parseRef(int i) {
        return Utils.bytesToInt(data, i);
    }



}
