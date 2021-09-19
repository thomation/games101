//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"

const int LUTSize = 1024;
double LUT[LUTSize] = {
0.0,0.0019543975323351244,0.003911344001784514,0.005870845230823149,0.007832907060397779,
0.009797535350001923,0.011764735977749342,0.013734514840450199,0.015706877853685897,0.017681830951884372,
0.019659380088396586,0.02163953123557194,0.02362229038483757,0.02560766354677258,0.02759565675118743,
0.029586276047201373,0.03157952750332001,0.03357541720751533,0.03557395126730425,0.03757513580982735,
0.039578976981929206,0.041585480950239444,0.04359465390125212,0.0456065020414081,0.04762103159717438,
0.04963824881512819,0.0516581599620383,0.05368077132494723,0.055706089211255146,0.05773411994880267,
0.05976486988595457,0.061798345391685904,0.06383455285566342,0.065873498688334,0.06791518932100835,
0.06995963120594749,0.072006830816449,0.07405679464693396,0.07610952921303424,0.07816504105168041,
0.08022333672119004,0.08228442280135496,0.08434830589353162,0.08641499262073102,0.08848448962770662,
0.09055680358104706,0.09263194116926506,0.0947099091028902,0.09679071411455889,0.09887436295910912,
0.10096086241367044,0.10305021927775958,0.10514244037337198,0.10723753254507666,0.10933550266011137,
0.11143635760847681,0.11354010430303316,0.1156467496795941,0.11775630069702582,0.1198687643373421,
0.12198414760580324,0.12410245753101184,0.12622370116501452,0.1283478855833978,0.13047501788538962,
0.13260510519395763,0.13473815465591177,0.13687417344200342,0.13901316874702882,0.14115514778992766,
0.1433001178138903,0.14544808608645773,0.14759905989962546,0.14975304656994898,0.1519100534386481,
0.15407008787171064,0.1562331572600002,0.15839926901936155,0.16056843059072798,0.16274064944022795,
0.1649159330592936,0.16709428896477016,0.1692757246990227,0.1714602478300485,0.17364786595158588,
0.1758385866832242,0.1780324176705185,0.18022936658509667,0.18242944112477713,0.18463264901367785,
0.18683899800233184,0.1890484958678028,0.19126115041379674,0.19347696947078083,0.19569596089609825,
0.19791813257408447,0.20014349241618404,0.2023720483610718,0.2046038083747676,0.20683878045075801,
0.2090769726101151,0.21131839290161705,0.21356304940187046,0.2158109502154301,0.21806210347492325,
0.22031651734117144,0.22257420000331476,0.22483515967893625,0.22709940461418704,0.22936694308391165,
0.23163778339177482,0.23391193387038878,0.23618940288143958,0.23847019881581724,0.24075433009374422,
0.24304180516490534,0.24533263250857673,0.24762682063375938,0.24992437807931134,0.25222531341407656,
0.25452963523702204,0.25683735217737025,0.25914847289473414,0.2614630060792529,0.2637809604517276,
0.2661023447637589,0.26842716779788356,0.2707554383677138,0.2730871653180774,0.27542235752515587,
0.2777610238966254,0.2801031733717993,0.28244881492177004,0.2847979575495517,0.28715061029022443,
0.2895067822110779,0.29186648241175833,0.29422972002441344,0.2965965042138396,0.29896684417763064,
0.3013407491463242,0.3037182283835544,0.30609929118619866,0.3084839468845305,0.3108722048423719,
0.31326407445724586,0.3156595651605276,0.3180586864176029,0.3204614477280199,0.3228678586256483,
0.32527792867883265,0.3276916674905531,0.33010908469858485,0.33253018997565453,0.33495499302960274,
0.3373835036035462,0.3398157314760377,0.3422516864612325,0.3446913784090484,0.34713481720533557,
0.3495820127720374,0.3520329750673624,0.35448771408594815,0.3569462398590324,0.35940856245462144,
0.3618746919776621,0.3643446385702117,0.3668184124116129,0.3692960237186648,0.37177748274579936,
0.3742627997852571,0.3767519851672622,0.37924504926020025,0.3817420024707983,0.38424285524430374,
0.3867476180646641,0.3892563014547094,0.39176891597633523,0.39428547223068533,0.3968059808583374,
0.3993304525394881,0.4018588979941419,0.4043913279822953,0.4069277533041296,0.4094681848001994,
0.41201263335162286,0.41456110988027717,0.4171136253489881,0.4196701907617269,0.42223081716380567,
0.4247955156420736,0.4273642973251166,0.42993717338345266,0.43251415502973684,0.4350952535189585,
0.43768048014864697,0.4402698462590737,0.44286336323345693,0.4454610424981701,0.4480628955229455,
0.4506689338210867,0.4532791689496747,0.45589361250978283,0.45851227614668555,0.4611351715500737,
0.46376231045426897,0.4663937046384396,0.4690293659268191,0.4716693061889213,0.4743135373397645,
0.4769620713400902,0.4796149201965862,0.48227209596210907,0.4849336107359125,0.48759947666386977,
0.4902697059387046,0.49294431080021917,0.4956233035355236,0.4983066964792703,0.5009945020138854,
0.5036867325698032,0.5063834006257046,0.5090845187087508,0.5117900993948267,0.5145001553087769,
0.5172146991246511,0.5199337435659451,0.5226573014058468,0.5253853854674813,0.5281180086241597,
0.5308551837996268,0.5335969239683148,0.5363432421555916,0.5390941514380176,0.5418496649435989,
0.5446097958520469,0.5473745573950336,0.550143962856453,0.5529180255726828,0.5556967589328482,
0.5584801763790854,0.5612682914068089,0.5640611175649782,0.566858668456371,0.5696609577378491,
0.5724679991206368,0.5752798063705926,0.5780963933084848,0.5809177738102747,0.5837439618073887,
0.5865749712870079,0.5894108162923448,0.5922515109229327,0.595097069334911,0.5979475057413132,
0.600802834412359,0.6036630696757447,0.606528225916939,0.6093983175794786,0.6122733591652639,
0.6151533652348625,0.6180383504078066,0.6209283293629003,0.6238233168385213,0.6267233276329311,
0.6296283766045825,0.6325384786724318,0.6354536488162518,0.6383739020769453,0.6412992535568642,
0.6442297184201289,0.6471653118929465,0.6501060492639382,0.6530519458844612,0.6560030171689374,
0.6589592785951826,0.6619207457047391,0.6648874341032074,0.6678593594605835,0.6708365375115968,
0.6738189840560497,0.6768067149591592,0.6797997461519041,0.6827980936313695,0.6858017734610956,
0.6888108017714312,0.6918251947598851,0.694844968691483,0.6978701398991253,0.7009007247839482,
0.7039367398156853,0.7069782015330345,0.7100251265440244,0.7130775315263849,0.7161354332279191,
0.7191988484668791,0.7222677941323421,0.725342287184591,0.7284223446554984,0.7315079836489071,
0.7345992213410217,0.7376960749807971,0.7407985618903307,0.7439066994652579,0.7470205051751491,
0.7501399965639131,0.7532651912501955,0.7563961069277885,0.7595327613660371,0.7626751724102522,
0.7658233579821221,0.7689773360801316,0.7721371247799812,0.7753027422350064,0.778474206676609,
0.7816515364146793,0.7848347498380306,0.78802386541483,0.7912189016930405,0.7944198773008545,
0.7976268109471416,0.800839721421891,0.8040586275966627,0.8072835484250381,0.8105145029430758,
0.8137515102697689,0.8169945896075063,0.820243760242538,0.8234990415454421,0.8267604529715947,
0.8300280140616468,0.8333017444419978,0.8365816638252782,0.8398677920108343,0.8431601488852145,
0.84645875442266,0.8497636286855981,0.8530747918251415,0.8563922640815882,0.8597160657849258,
0.86304621735534,0.8663827393037273,0.8697256522322067,0.8730749768346424,0.8764307338971646,
0.8797929442986943,0.8831616290114752,0.8865368091016069,0.8899185057295809,0.8933067401508228,
0.8967015337162371,0.9001029078727569,0.9035108841638937,0.9069254842302988,0.910346729810319,
0.9137746427405656,0.9172092449564787,0.9206505584929052,0.9240986054846712,0.9275534081671638,
0.9310149888769206,0.934483370052212,0.937958574233642,0.94144062406474,0.94492954229257,
0.9484253517683289,0.9519280754479654,0.9554377363927912,0.9589543577701023,0.9624779628538035,
0.9660085750250376,0.969546217772819,0.9730909146946728,0.9766426894972764,0.9802015659971087,
0.9837675681211028,0.9873407199073022,0.9909210455055241,0.9945085691780267,0.9981033153001805,
1.0017053083611465,1.0053145729645567,1.0089311338292046,1.012555015789733,1.016186243797336,
1.0198248429204595,1.0234708383455098,1.027124255377565,1.0307851194410989,1.0344534560807,
1.0381292909618025,1.0418126498714244,1.0455035587189043,1.049202043536649,1.0529081304808874,
1.0566218458324261,1.0603432159974142,1.0640722675081113,1.0678090270236642,1.0715535213308873,
1.075305777345051,1.0790658221106733,1.0828336828023186,1.086609386725407,1.090392961317023,
1.0941844341467322,1.097983832917411,1.1017911854660707,1.105606519764701,1.1094298639211086,
1.1132612461797722,1.1171006949226943,1.1209482386702718,1.124803906082159,1.1286677259581506,
1.1325397272390636,1.1364199390076295,1.14030839048939,1.144205111053607,1.1481101302141705,
1.1520234776305234,1.1559451831085823,1.1598752766016789,1.163813788211496,1.167760748189022,
1.1717161869355046,1.1756801350034167,1.1796526230974307,1.1836336820753954,1.1876233429493284,
1.1916216368864085,1.1956285952099834,1.199644249400582,1.2036686310969311,1.2077017720969898,
1.2117437043589847,1.2157944600024548,1.2198540713093082,1.223922570724884,1.227999990859025,
1.2320863644871565,1.2361817245513795,1.2402861041615667,1.24439953659647,1.2485220553048397,
1.2526536939065491,1.2567944861937304,1.26094446613192,1.2651036678612126,1.2692721256974269,
1.2734498741332776,1.277636947839562,1.2818333816663512,1.2860392106441956,1.2902544699853395,
1.2944791950849437,1.298713421522323,1.3029571850621882,1.3072105216559047,1.3114734674427586,
1.315746058751233,1.3200283321002972,1.3243203242007064,1.3286220719563122,1.3329336124653837,
1.3372549830219418,1.3415862211171037,1.3459273644404381,1.350278450881337,1.3546395185303908,
1.3590106056807856,1.3633917508297024,1.3677829926797385,1.3721843701403338,1.3765959223292126,
1.3810176885738374,1.385449708412878,1.3898920215976898,1.3943446680938072,1.3988076880824496,
1.4032811219620425,1.4077650103497483,1.4122593940830166,1.4167643142211424,1.421279812046841,
1.4258059290678382,1.430342707018472,1.4348901878613116,1.4394484137887886,1.4440174272248438,
1.4485972708265906,1.4531879874859905,1.4577896203315452,1.4624022127300051,1.4670258082880938,
1.4716604508542444,1.4763061845203556,1.4809630536235645,1.485631102748032,1.4903103767267476,
1.4950009206433503,1.499702779833967,1.5044159998890627,1.5091406266553204,1.5138767062375225,
1.5186242850004634,1.5233834095708707,1.5281541268393497,1.5329364839623463,1.5377305283641234,
1.5425363077387628,1.5473538700521792,1.55218326354416,1.557024536730418,1.5618777384046698,
1.5667429176407286,1.5716201237946223,1.5765094065067267,1.581410815703922,1.5863244016017706,
1.5912502147067131,1.5961883058182944,1.6011387260313927,1.6061015267384917,1.6110767596319615,
1.6160644767063652,1.6210647302607886,1.6260775729011927,1.6311030575427883,1.6361412374124373,
1.6411921660510695,1.646255897316135,1.6513324853840716,1.6564219847527994,1.6615244502442408,
1.6666399370068676,1.6717685005182714,1.6769101965877555,1.6820650813589615,1.687233211312517,
1.6924146432687113,1.697609434390196,1.7028176421847165,1.7080393245078693,1.7132745395658864,
1.7185233459184535,1.7237858024815456,1.7290619685303041,1.7343519037019393,1.7396556679986575,
1.7449733217906254,1.7503049258189602,1.755650541198756,1.7610102294221355,1.766384052361336,
1.7717720722718318,1.7771743517954814,1.7825909539637161,1.7880219422007486,1.7934673803268406,
1.7989273325615711,1.8044018635271701,1.8098910382518678,1.8153949221732897,1.8209135811418828,
1.8264470814243818,1.8319954897073083,1.8375588731005088,1.8431372991407389,1.848730835795271,
1.8543395514655563,1.8599635149909102,1.865602795652259,1.871257463175904,1.876927587737346,
1.8826132399651383,1.888314490944792,1.8940314122227144,1.8997640758102006,1.9055125541874633,
1.9112769203077071,1.917057247601248,1.9228536099796867,1.928666081840116,1.9344947380693802,
1.9403396540483904,1.946200905656473,1.9520785692757818,1.9579727217957472,1.9638834406175902,
1.96981080365887,1.9757548893581018,1.98171577667941,1.9876935451172515,1.9936882747011757,
1.9997000460006558,2.005728940129963,2.0117750387531035,2.0178384240888114,2.0239191789156004,
2.0300173865768687,2.036133130986077,2.042266496631967,2.04841756858386,2.054586432497008,
2.0607731746180065,2.06697788179028,2.073200641459622,2.079441541679811,2.0857006711182824,
2.0919781190618796,2.0982739754226625,2.104588330743797,2.110921276205506,2.1172729036310978,
2.123643305493065,2.130032574919256,2.136440805699129,2.1428680922900716,2.149314529823802,
2.155780214112856,2.162265241657137,2.1687697096505683,2.1752937159878067,2.181837359271051,
2.1884007388169358,2.194983954663505,2.2015871075772724,2.208210299060383,2.2148536313578413,
2.2215172074648546,2.2282011311342553,2.2349055068840484,2.2416304400049016,2.2483760365680476,
2.255142403432966,2.261929648255324,2.2687378794949913,2.275567206424143,2.2824177391354903,
2.2892895885506035,2.296182866428337,2.3030976853733773,2.3100341588448967,2.316992401165317,
2.3239725275291967,2.3309746540122207,2.337998897580326,2.3450453760989323,2.352114208342308,
2.3592055140030483,2.3663194137016914,2.3734560289964524,2.3806154823930945,2.3877978973549356,
2.3950033983129795,2.402232110676194,2.4094841608419184,2.416759676206426,2.424058785175618,
2.4313816171758678,2.43872830266502,2.446098973143527,2.453493761165757,2.460912800351439,
2.4683562253972835,2.475824172088755,2.4833167773120106,2.490834179066008,2.4983765164747793,
2.505943929799883,2.513536560453027,2.5211545510088693,2.528798045218008,2.536467188020152,
2.544162125557467,2.551883005188141,2.5596299755001173,2.567403186325042,2.575202788752402,
2.583028935143879,2.5908817791479017,2.5987614757144195,2.6066681811098817,2.6146020529324487,
2.6225632501274156,2.6305519330028737,2.6385682632455905,2.6466124039371435,2.654684519570275,
2.662784776065509,2.6709133407880015,2.6790703825646576,2.687256071701491,2.6954705800012673,
2.7037140807813937,2.7119867488920963,2.7202887607348614,2.728620294281176,2.7369815290915396,
2.745372646334781,2.7537938288076598,2.7622452609547943,2.770727128888876,2.779239620411215,
2.7877829250325954,2.7963572339944727,2.8049627402904855,2.813599638688336,2.822268125751981,
2.8309683998642083,2.83970066124955,2.8484651119975872,2.857261956086598,2.866091399407614,
2.8749536497888535,2.8838489170205484,2.892777412880186,2.9017393511581475,2.9107349476837867,
2.9197644203519184,2.9288279891497497,2.9379258761842646,2.9470583057100583,2.9562255041576275,
2.9654277001621416,2.974665124592705,2.9839380105820874,2.9932465935569823,3.0025911112687615,
3.011971803824759,3.021388913720089,3.0308426858700015,3.0403333676428073,3.0498612088933563,
3.059426461997104,3.069029381884763,3.078670226077567,3.0883492547231444,3.098066730632018,
3.107822919314756,3.117618089019775,3.1274525107718127,3.137326458411085,3.147240208633147,
3.1571940410294546,3.167188238128681,3.177223085438751,3.1872988714896513,3.1974158878770234,
3.207574429306537,3.2177747936390935,3.2280172819368445,3.238302198510071,3.248629850964923,
3.259000550252055,3.2694146107161584,3.2798723501464284,3.290374089827983,3.3009201545942366,
3.3115108728802864,3.3221465767772975,3.3328276020879324,3.3435542883828435,3.35432697905825,
3.365146021394625,3.3760117666165224,3.386924569953566,3.397884790702632,3.408892792291243,
3.419948942342227,3.431053612739633,3.4422071796959677,3.4534100238207714,3.464662530190552,
3.475965088420145,3.4873180927354963,3.498721942047912,3.5101770400298418,3.5216837951921853,
3.5332426209631898,3.54485393576897,3.5565181631157055,3.568235731673514,3.5800070753620963,
3.5918326334381603,3.6037128505846914,3.6156481770020936,3.627639068501258,3.639685986598637,
3.651789398613311,3.6639497777661765,3.6761676032812325,3.688443360489091,3.700777540932719,
3.7131706424754825,3.7256231694115836,3.738135632578899,3.7507085494743366,3.7633424443717405,
3.7760378484424253,3.7887952998784282,3.80161534401851,3.814498533477029,3.827445428275721,
3.8404565959784978,3.8535326118293383,3.866674058893333,3.879881528201024,3.8931556188960634,
3.9064969383863466,3.9199061024986745,3.9333837356370567,3.9469304709447837,3.9605469504703312,
3.974233825337235,3.9879917559180513,4.001821412012513,4.015723473029996,4.029698628176441,
4.04374757664585,4.057871027816482,4.072069701451922,4.086344327907112,4.100695648339566,
4.115124414925847,4.129631391083529,4.144217351698763,4.1588830833596715,4.173629384595682,
4.188457066123043,4.20336695109668,4.218359875368615,4.233436687753111,4.248598250298818,
4.263845438568077,4.2791791419236604,4.29460026382315,4.310109722121222,4.325708449380097,
4.341397393188385,4.357177516488654,4.373049797913956,4.38901523213366,4.405074830208839,
4.421229619957593,4.437480646330591,4.453828971797221,4.470275676742668,4.486821859876328,
4.50346863865192,4.5202171496997225,4.537068549271348,4.554024013697488,4.5710847398590815,
4.5882519456724244,4.6055268705886405,4.6229107761081005,4.640404946310289,4.658010688399684,
4.67572933326825,4.6935622360751275,4.711510776844195,4.729576361080085,4.7477604204034884,
4.7660644132062915,4.784489825327458,4.80303817075035,4.821710992322323,4.840509862497512,
4.859436384103633,4.878492191133773,4.897678949564177,4.916998358199003,4.93645214954318,
4.956042090704453,4.975769984325826,4.9956376695496045,5.015647023014381,5.03579995988625,
5.0560984349257785,5.076544443592101,5.097140023185811,5.117887254032241,5.138788260706836,
5.159845213304516,5.181060328754818,5.202435872184923,5.2239741583325765,5.245677553011218,
5.267548474629528,5.289589395767949,5.311802844814701,5.334191407663978,5.356757729479295,
5.379504516524866,5.4024345380683085,5.42555062835794,5.448855688678256,5.4723526894873435,
5.496044672640104,5.519934753701527,5.5440261243544215,5.568322054906191,5.592825896899695,
5.617541085833345,5.642471143995988,5.667619683422462,5.692990408975983,5.7185871215640365,
5.744413721494681,5.77047421198072,5.796772702799695,5.8233134141179566,5.85010068048782,
5.877138955027288,5.904432813792355,5.931986960352752,5.959806230582507,5.98789559767757,
6.016260177413587,6.044905233657626,6.073836184148867,6.103058606564044,6.132578244884679,
6.1624010160843445,6.1925330171553785,6.222980532495988,6.253750041680155,6.284848227634353,
6.316281985246983,6.348058430438191,6.380184909720033,6.4126690102790835,6.445518570616136,
6.478741691780402,6.512346749238384,6.5463424054210995,6.580737622996638,6.615541678918905,
6.6507641793077905,6.686415075220413,6.722504679378278,6.759043683920771,6.796043179261403,
6.833514674130128,6.871470116892358,6.909921918243511,6.9488829753869945,6.988366697813603,
7.028387034811137,7.0689585048457095,7.110096226969512,7.151815954425128,7.194134110633465,
7.237067827770906,7.280634988162735,7.324854268743029,7.369745188857774,7.415328161717538,
7.461624549839172,7.508656724853573,7.55644813209864,7.605023360464423,7.654408218011318,
7.704629813943678,7.755716647590669,7.807698705125756,7.860607564846755,7.914476511942008,
7.969340663787385,8.025237106955142,8.082205047273659,8.14028597445857,8.199523843047244,
8.259965271612897,8.321659762520534,8.384659944819926,8.449021843261914,8.514805176883684,
8.58207369115107,8.650895528287666,8.721343641183559,8.793496257186112,8.867437399165631,
8.943257472558404,9.021053928673393,9.100932016469464,9.183005637351922,9.26739832040776,
9.354244339034855,9.443689994301499,9.535895095832853,9.631034677868895,9.729300996783444,
9.830905867345637,9.936083409084626,10.04509329229691,10.158224596907983,10.275800428505564,
10.398183477135007,10.525782759790712,10.659061862576317,10.798549101514476,10.944850164246635,
11.098663996996827,11.260802990875426,11.432218944003013,11.61403690360277,11.807599944654518,
12.014529421131828,12.236807584818614,12.47689334104858,12.737888491927981,13.02378343861285,
13.339832780822519,13.693153071537806,14.093721822155713,14.556151823810902,15.103097846168856,
15.772513242206267,16.635547592033756,17.851934439408932,19.931370894861956,
};

void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of the Whitted-syle light transport algorithm (E [S*] (D|G) L)
//
// This function is the function that compute the color at the intersection point
// of a ray defined by a position and a direction. Note that thus function is recursive (it calls itself).
//
// If the material of the intersected object is either reflective or reflective and refractive,
// then we compute the reflection/refracton direction and cast two new rays into the scene
// by calling the castRay() function recursively. When the surface is transparent, we mix
// the reflection and refraction color using the result of the fresnel equations (it computes
// the amount of reflection and refractin depending on the surface normal, incident view direction
// and surface refractive index).
//
// If the surface is duffuse/glossy we use the Phong illumation model to compute the color
// at the intersection point.
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    if (depth > this->maxDepth) {
        return Vector3f(0.0,0.0,0.0);
    }
    Intersection intersection = Scene::intersect(ray);
    Material *m = intersection.m;
    Object *hitObject = intersection.obj;
    Vector3f hitColor = this->backgroundColor;
//    float tnear = kInfinity;
    Vector2f uv;
    uint32_t index = 0;
    if(intersection.happened) {
        //return Vector3f(0, 0, 0);
        //std::cout << "hit " << intersection.coords << std::endl;
        Vector3f hitPoint = intersection.coords;
        Vector3f N = intersection.normal; // normal
        Vector2f st; // st coordinates
        hitObject->getSurfaceProperties(hitPoint, ray.direction, index, uv, N, st);
//        Vector3f tmp = hitPoint;
        switch (m->getType()) {
            case REFLECTION_AND_REFRACTION:
            {
                hitPoint = computeReflectionAndFefraction(ray, depth, hitPoint, N, m);
                break;
            }
            case REFLECTION:
            {
                hitColor = computeReflection(ray, depth, hitPoint, N, m);
				break;
            }
           case DIFFUSE_AND_GLOSSY :
            {
			    hitColor = computeDiffuseAndGlossy(ray, depth, hitPoint, N, m, st, hitObject);
                break;
            }
           case SUBSURFACE_SCATTERING: 
           {
			   bool suc = false;
               hitColor = computeSubsurfaceScattering(ray, depth, hitPoint, N, m, st, hitObject, suc);
			   if(!suc)
				   hitColor = computeDiffuseAndGlossy(ray, depth, hitPoint, N, m, st, hitObject);
           }
        }
    }

    return hitColor;
}

    // Compute Fresnel equation
	//
	// \param I is the incident view direction
	//
	// \param N is the normal at the intersection point
	//
	// \param ior is the material refractive index
	//
	// \param[out] kr is the amount of light reflected
    static void fresnel(const Vector3f &I, const Vector3f &N, const float &ior, float &kr)
    {
        float cosi = clamp(-1, 1, dotProduct(I, N));
        float etai = 1, etat = ior;
        if (cosi > 0) {  std::swap(etai, etat); }
        // Compute sini using Snell's law
        float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
        // Total internal reflection
        if (sint >= 1) {
            kr = 1;
        }
        else {
            float cost = sqrtf(std::max(0.f, 1 - sint * sint));
            cosi = fabsf(cosi);
            float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
            float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
            kr = (Rs * Rs + Rp * Rp) / 2;
        }
        // As a consequence of the conservation of energy, transmittance is given by:
        // kt = 1 - kr;
    } 
	
	// Compute refraction direction using Snell's law
	//
	// We need to handle with care the two possible situations:
	//
	//    - When the ray is inside the object
	//
	//    - When the ray is outside.
	//
	// If the ray is outside, you need to make cosi positive cosi = -N.I
	//
	// If the ray is inside, you need to invert the refractive indices and negate the normal N
	static Vector3f refract(const Vector3f& I, const Vector3f& N, const float& ior)
	{
		float cosi = clamp(-1, 1, dotProduct(I, N));
		float etai = 1, etat = ior;
		Vector3f n = N;
		if (cosi < 0) { cosi = -cosi; }
		else { std::swap(etai, etat); n = -N; }
		float eta = etai / etat;
		float k = 1 - eta * eta * (1 - cosi * cosi);
		return k < 0 ? 0 : eta * I + (eta * cosi - sqrtf(k)) * n;
	}


Vector3f Scene::computeReflectionAndFefraction(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
	Vector3f reflectionDirection = normalize(reflect(ray.direction, N));
	Vector3f refractionDirection = normalize(refract(ray.direction, N, m->ior));
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f refractionRayOrig = (dotProduct(refractionDirection, N) < 0) ?
								 hitPoint - N * EPSILON :
								 hitPoint + N * EPSILON;
	Vector3f reflectionColor = castRay(Ray(reflectionRayOrig, reflectionDirection), depth + 1);
	Vector3f refractionColor = castRay(Ray(refractionRayOrig, refractionDirection), depth + 1);
	float kr;
	fresnel(ray.direction, N, m->ior, kr);
	return reflectionColor * kr + refractionColor * (1 - kr);
}
Vector3f Scene::computeReflection(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m) const
{
    float kr;
	fresnel(ray.direction, N, m->ior, kr);
	Vector3f reflectionDirection = reflect(ray.direction, N);
	Vector3f reflectionRayOrig = (dotProduct(reflectionDirection, N) < 0) ?
								 hitPoint + N * EPSILON :
								 hitPoint - N * EPSILON;
	return  castRay(Ray(reflectionRayOrig, reflectionDirection),depth + 1) * kr;
}
Vector3f Scene::computeDiffuseAndGlossy(const Ray &ray, int depth, const Vector3f& hitPoint, const Vector3f& N, Material * m, const Vector2f& st, Object * hitObject) const
{
	// [comment]
	// We use the Phong illumation model int the default case. The phong model
	// is composed of a diffuse and a specular reflection component.
	// [/comment]
	Vector3f lightAmt = 0, specularColor = 0;
	Vector3f shadowPointOrig = (dotProduct(ray.direction, N) < 0) ?
							   hitPoint + N * EPSILON :
							   hitPoint - N * EPSILON;
	// [comment]
	// Loop over all lights in the scene and sum their contribution up
	// We also apply the lambert cosine law
	// [/comment]
	for (uint32_t i = 0; i < get_lights().size(); ++i)
	{
		auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
		if (area_ptr)
		{
			// Do nothing for this assignment
		}
		else
		{
			Vector3f lightDir = get_lights()[i]->position - hitPoint;
			// square of the distance between hitPoint and the light
			float lightDistance2 = dotProduct(lightDir, lightDir);
			lightDir = normalize(lightDir);
			float LdotN = std::max(0.f, dotProduct(lightDir, N));
			Object *shadowHitObject = nullptr;
			float tNearShadow = kInfinity;
			// is the point in shadow, and is the nearest occluding object closer to the object than the light itself?
			bool inShadow = bvh->Intersect(Ray(shadowPointOrig, lightDir)).happened;
			lightAmt += (1 - inShadow) * get_lights()[i]->intensity * LdotN;
			Vector3f reflectionDirection = reflect(-lightDir, N);
			specularColor += powf(std::max(0.f, -dotProduct(reflectionDirection, ray.direction)),
								  m->specularExponent) * get_lights()[i]->intensity;
		}
	}
	return lightAmt * (hitObject->evalDiffuseColor(st) * m->Kd + specularColor * m->Ks);
}

static Vector3f toWorld(const Vector3f& a, const Vector3f& N) {
	Vector3f B, C;
	if (std::fabs(N.x) > std::fabs(N.y)) {
		float invLen = 1.0f / std::sqrt(N.x * N.x + N.z * N.z);
		C = Vector3f(N.z * invLen, 0.0f, -N.x * invLen);
	}
	else {
		float invLen = 1.0f / std::sqrt(N.y * N.y + N.z * N.z);
		C = Vector3f(0.0f, N.z * invLen, -N.y * invLen);
	}
	B = crossProduct(C, N);
	return a.x * B + a.y * C + a.z * N;
}
static float Rd(float r, float d)
{
	if (r == 0.0f)
		return 0.0f;
	return (std::exp(-r / d) + std::exp(-r / (3.0f * d))) /(8.0f * M_PI * d * r);
}
static Vector3f Rd(float r, const Vector3f& D)
{
	return Vector3f(Rd(r, D.x), Rd(r, D.y), Rd(r, D.z));
}
static float computeR(float r, float d)
{
	float offset = std::min(r * LUTSize, LUTSize - 1.0f);
	const int ib = (int)offset;
	const int iu = (int)(offset + 1.0f);
	const float distance = LUT[ib] * (1 - offset + ib) + LUT[iu] * (offset - ib);
	return distance * d;
}
bool static samplePointPreCompute(const Scene* scene, const Vector3f& source, const Vector3f& N, const Vector3f& D,
	Vector3f& target, float& pdf)
{
	//get one d with random channel
	int channel = (int)std::min(3.0f * get_random_float(), 2.0f);
	auto d = D[channel];
	auto r = computeR(get_random_float(), d);
	auto Rm = computeR(0.996f, d);
	if (r > Rm || r < EPSILON)
		return false;
	float theta = 2.0 * M_PI * get_random_float();
	Vector3f local_dir(std::cos(theta), std::sin(theta), 0.0);
	auto dir = toWorld(normalize(local_dir), N);
	Vector3f pos = source + dir * r + N * sqrt(Rm * Rm - r * r);
	//Vector3f T = normalize(pos - source);
	//auto d = dotProduct(T, N);
	//std::cout << d << std::endl;
	Ray ray = Ray(pos, -N);
	Intersection inter = scene->intersect(ray);
	if (!inter.happened)
		return false;
	target = inter.coords;
	auto dis2 = dotProduct(source - target, source - target);
	if (dis2 > Rm * Rm)
		return false;
	auto VNhit = std::abs(dotProduct(inter.normal, N));
	pdf = Rd(r, d) * VNhit / 3.0f;
	return VNhit > 0.1;
}
const float D2Rm = 12;
bool static samplePointMis(const Scene * scene, const Vector3f & source, const Vector3f& N, const Vector3f & D,
	Vector3f & target, float & pdf)
{
	//get one d with random channel
	const int channel = (int)std::min(3.0f * get_random_float() , 2.0f);
	const float d = D[channel];
	const float Rm = d * D2Rm;
	float r;
	//random weight to select a strategy for r 
	const float w1 = 1.0f - exp(-Rm / d);
	const float w2 = 1.0f - exp(-Rm / (3 * d));
	const float w = (w1 + w2) * get_random_float();
	if (w < w1)
	{
		r = -d * log(1.0f - get_random_float() * (1.0f - exp(-Rm / d)));
		pdf = w1 / (w1 + w2);
	}
	else
	{
		r = -3 * d * log(1.0f - get_random_float() * (1.0f - exp(-Rm / (3 * d))));
		pdf = w2 / (w1 + w2);
	}
	pdf *= (exp(-r / d) / (2 * M_PI * d * r) / (1 - exp(-Rm / d))
			+ exp(-r / (3 * d)) / (2 * M_PI * d * r) / (3 * (1 - exp(-Rm / (3 * d)))));

	if (r > Rm || r < EPSILON)
		return false;
	float theta = 2.0 * M_PI * get_random_float();
	Vector3f local_dir(std::cos(theta), std::sin(theta), 0.0);
	auto dir = toWorld(normalize(local_dir), N);
	Vector3f pos = source + dir * r + N * sqrt(Rm * Rm - r * r);
	//Vector3f T = normalize(pos - source);
	//auto d = dotProduct(T, N);
	//std::cout << d << std::endl;
	Ray ray = Ray(pos, -N);
    Intersection inter = scene->intersect(ray);
	if (!inter.happened)
		return false;
	target = inter.coords;
	auto dis2 = dotProduct(source - target, source - target);
	if (dis2 > Rm * Rm)
		return false;
	auto VNhit = std::abs(dotProduct(inter.normal, N));
	pdf *= VNhit / 3.0f;
	return VNhit > 0.01;
}
// wi and wo ara all towards to surface
// Ni and No are all from surface
static Vector3f S(const Vector3f& po, const Vector3f& wo, const Vector3f& No, float ioro,
	const Vector3f& pi, const Vector3f& wi, const Vector3f& Ni, float iori, const Vector3f& D)
{
	float kri;
	fresnel(wi, Ni, iori, kri);
	float kro;
	auto wor = refract(wo, No, ioro);
	fresnel(-wor, No, ioro, kro);
	float d = sqrt(dotProduct(po - pi, po - pi));
	return /*(1 - kro) */ Rd(d, D) * (1 - kri) / M_PI;
}
Vector3f Scene::computeSubsurfaceScattering(const Ray &ray, int depth, const Vector3f& po, const Vector3f& No, Material * mo, const Vector2f& st, Object * hitObject,
											bool & suc) const
{
	Vector3f resultColor = Vector3f(0);
	const Vector3f A = hitObject->evalDiffuseColor(st);
	const Vector3f D = mo->Ld * (Vector3f(3.5) + 100 * (A - 0.33) * (A - 0.33) * (A - 0.33) * (A - 0.33)).Inverse();

	Vector2f ist; // st coordinates
	uint32_t index = 0;
	Vector2f iuv;
	Vector3f sample;
	float pdf;

	//if (samplePointMis(this, po, No, D, sample, pdf))
	if (samplePointPreCompute(this, po, No, D, sample, pdf))
	{
		for (uint32_t i = 0; i < get_lights().size(); ++i)
		{
			auto area_ptr = dynamic_cast<AreaLight*>(this->get_lights()[i].get());
			if (area_ptr)
				continue;

			Vector3f inLightDir = sample - get_lights()[i]->position;
			inLightDir = normalize(inLightDir);
			auto inter = Scene::intersect(Ray(get_lights()[i]->position, inLightDir));
			if (!inter.happened)
				continue;
			auto dis2 = dotProduct(inter.coords - sample, inter.coords - sample);
			if (dis2 > 0.01)
				continue;
			Material* mi = inter.m;
			Object* inObject = inter.obj;
			const Vector3f& pi = inter.coords;
			Vector3f Ni = inter.normal; // normal
			inObject->getSurfaceProperties(pi, inLightDir, index, iuv, Ni, ist);
			float LdotN = std::max(0.f, dotProduct(-inLightDir, Ni));
			resultColor += S(po, ray.direction, No, mo->ior, pi, inLightDir, Ni, mi->ior, D)
				* get_lights()[i]->intensity * LdotN
				/ pdf
				* A * mo->Kss;
			suc = true;
		}
	}
	return resultColor;
}