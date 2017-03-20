package com.bushaopeng.android.parseapk;


import com.bushaopeng.android.parseapk.base.DexData;
import com.bushaopeng.android.parseapk.base.DexDataItem;
import com.bushaopeng.android.parseapk.data.MethodContent;
import com.bushaopeng.android.parseapk.refs.MethodRef;
import com.bushaopeng.android.parseapk.utils.Utils;

import java.util.Map;

/**
 * Created by bsp on 17/3/18.
 */
public class MethodIdsItem extends DexDataItem<MethodRef, MethodContent> {
    public MethodIdsItem(String name) {
        super(name);
    }

    @Override
    protected MethodRef[] createRefs() {
        return new MethodRef[count];
    }

    @Override
    protected int getRefSize() {
        return MethodRef.SIZE;
    }

    @Override
    protected MethodRef parseRef(int i) {
        MethodRef methodRef = new MethodRef();
        methodRef.classIdx = Utils.u2ToInt(data, i);
        methodRef.protoIdx = Utils.u2ToInt(data, i + 2);
        methodRef.nameIdx = Utils.bytesToInt(data, i + 4);
        return methodRef;
    }

    @Override
    public void parse3rdRealData(Map<String, DexDataItem> dataItems, byte[] dexData) {
        TypeIdsItem item = (TypeIdsItem) dataItems.get(DexData.TYPE_IDS);
        StringIdsItem sItem = (StringIdsItem) dataItems.get(DexData.STRING_IDS);
        ProtoIdsItem pItem = (ProtoIdsItem) dataItems.get(DexData.PROTO_IDS);
        this.realData = new MethodContent[refs.length];
        for (int i = 0; i < refs.length; i++) {
            MethodContent protoContent = new MethodContent();
            protoContent.proto = pItem.realData[refs[i].protoIdx].shorty;
            protoContent.name = sItem.realData[refs[i].nameIdx];
            protoContent.className = item.realData[refs[i].classIdx];
            this.realData[i] = protoContent;
        }
    }
}
