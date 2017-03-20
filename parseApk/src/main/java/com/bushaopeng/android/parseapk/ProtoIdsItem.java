package com.bushaopeng.android.parseapk;


import com.bushaopeng.android.parseapk.base.DexData;
import com.bushaopeng.android.parseapk.base.DexDataItem;
import com.bushaopeng.android.parseapk.data.ProtoContent;
import com.bushaopeng.android.parseapk.refs.ProtoRef;
import com.bushaopeng.android.parseapk.utils.Utils;

import java.util.Map;

/**
 * Created by bsp on 17/3/18.
 */
public class ProtoIdsItem extends DexDataItem<ProtoRef, ProtoContent> {
    public ProtoIdsItem(String name) {
        super(name);
    }

    @Override
    protected ProtoRef[] createRefs() {
        return new ProtoRef[count];
    }

    @Override
    protected int getRefSize() {
        return ProtoRef.SIZE;
    }

    @Override
    protected ProtoRef parseRef(int i) {
        ProtoRef protoRef = new ProtoRef();
        protoRef.shortyIdx = Utils.bytesToInt(data, i);
        i += 4;
        protoRef.returnTypeIdx = Utils.bytesToInt(data, i);
        i += 4;
        protoRef.parametersOff = Utils.bytesToInt(data, i);
        return protoRef;
    }

    @Override
    public void parse2ndRealData(Map<String, DexDataItem> dataItems, byte[] dexData) {
        TypeIdsItem item = (TypeIdsItem) dataItems.get(DexData.TYPE_IDS);
        StringIdsItem sItem = (StringIdsItem) dataItems.get(DexData.STRING_IDS);
        String[] realData = item.realData;
        this.realData = new ProtoContent[refs.length];
        for (int i = 0; i < refs.length; i++) {
            ProtoContent protoContent = new ProtoContent();
            protoContent.shorty = sItem.realData[refs[i].shortyIdx];
            protoContent.returnType = realData[refs[i].returnTypeIdx];
            this.realData[i] = protoContent;
        }
    }
}
