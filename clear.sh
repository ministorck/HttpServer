#!/bin/bash
find ./bin -name "SHttpServer*" | xargs rm -rfv
find ./src -name "moc_*" | xargs rm -rfv
find ./src -name "Makefile*" | xargs rm -rfv
find ./src -name "*.o" | xargs rm -rfv
find ./src -name "ui_*.h" | xargs rm -rfv
find ./src -name "Http.pro.user*" | xargs rm -rfv
find ./src -name "object_script.SHttpServer*" | xargs rm -rfv
find ./lib -name "lib*.so*" | xargs rm -rfv
find ./lib -name "*.a" | xargs rm -rfv
find ./lib -name "*.dll" | xargs rm -rfv
