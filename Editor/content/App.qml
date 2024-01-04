// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.2
import Editor

Window {
    width: mainScreen.width
    height: mainScreen.height

    visible: true
    title: "Editor"

    //Screen01 {
     //   id: mainScreen
    //}
    SceneEditor{
        id:defaultEditor
        x: 0
        y: 0
        width: 1920
        height: 1080
    }

}

