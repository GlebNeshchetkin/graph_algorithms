#include <iostream>
#include "include/lca.hpp"


int main()
{
    TarjanLCA<int> lca;
    lca.addEdge(1,2);
    lca.addEdge(1,3);
    lca.addEdge(1,4);
    lca.addEdge(3,5);
    lca.addEdge(3,6);
    lca.addQuery(5,6,0);
    lca.addQuery(2,6,1);
    lca.addQuery(3,4,2);

    auto ans = lca.solve(1);
    std::cout << ans[0] << std::endl;
    std::cout << ans[1] << std::endl;
    std::cout << ans[2] << std::endl;
}