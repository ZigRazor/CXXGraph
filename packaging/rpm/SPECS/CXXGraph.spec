Name:           CXXGraph
Version:        0.1
Release:        4%{?dist}
Summary:        Header-Only C++ Library for Graph Representation and Algorithms
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
Prefix:/usr

License:        AGPLv3.0
URL:            https://github.com/ZigRazor/CXXGraph
Source0:        https://github.com/ZigRazor/CXXGraph/archive/refs/tags/v0.1.4.tar.gz

#Requires:       bash

BuildArch:      noarch

%define _topdir %(echo $PWD)/
%description
Header-Only C++ Library for Graph Representation, Manipulation, Partitioning and Algorithms

%precd rm
echo "  |------------------------------------------------| "
echo "  |------------   CXXGraph Library   --------------| "
echo "  |------------------------------------------------| "


%prep
cd %{_topdir}
#%{_topdir}/../targzip.sh
../targzip.sh

%build

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{prefix}/include
cp -rp %{_topdir}/../../include/* %{buildroot}%{prefix}/include/

echo "  |------------------------------------------------| "
echo "  |--------   Installation Completed   ------------| "
echo "  |------------------------------------------------| "

%preun
echo "  |------------------------------------------------| "
echo "  |------------   CXXGraph Library   --------------| "
echo "  |------------------------------------------------| "

%postun
rm -rf /usr/include/Graph.hpp /usr/include/CXXGraphConfig.h
echo "  |------------------------------------------------| "
echo "  |-------   Uninstallation Completed   -----------| "
echo "  |------------------------------------------------| "

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
            %{prefix}/include

%changelog
* Mon Jul 26 2021 ZigRazor <zigrazor@gmail.com> - 0.1-4
- First RPM package